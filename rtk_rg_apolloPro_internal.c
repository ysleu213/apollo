
#ifdef CONFIG_APOLLOPRO_MODEL
#include <rtl_glue.h>
extern rtk_fb_debug_level_t debug_level;
#else
#include <rtk_rg_internal.h>
#endif
#include <rtk_rg_apolloPro_internal.h>

#ifdef CONFIG_RTL9607B_SERIES

rtk_rg_fbDatabase_t rgpro_db;


static void *_rtk_rg_memoryAlignAlloc(uint32 alignedSize, uint32 size)
{
	void *ptr = NULL;
	uint32 mask = ~(alignedSize -1);
#ifndef CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC
	rgpro_db.ddrMemAlloc = &rgpro_db.ddrMemBlock;

#else //CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC

#ifdef __KERNEL__	
	if((rgpro_db.ddrMemAlloc = kmalloc(sizeof(size + (alignedSize - 1)), GFP_ATOMIC)) == NULL) {
		return NULL;
	}
#else
	if((rgpro_db.ddrMemAlloc = rtlglue_malloc(sizeof(size + (alignedSize - 1)))) == NULL) {
		return NULL;
	}
#endif

#endif //CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC

	TRACE("ddr memory block @ %p", &rgpro_db.ddrMemBlock);
	memset(rgpro_db.ddrMemAlloc, 0, sizeof((size + (alignedSize - 1))));
	ptr = (void *) (((long)rgpro_db.ddrMemAlloc + (alignedSize - 1)) & mask);

	return ptr;
}

uint32 _rtk_rg_flowEntryValidBitIgnoreRst(rtk_enable_t state)
{
	if((state != DISABLED) && (state != ENABLED))
		return FAIL;
	rgpro_db.ignoreFlowValidTableRst = state;

	return SUCCESS;
}

uint32 _rtk_rg_flowEntryValidBit_reset()
{
	if(!rgpro_db.ignoreFlowValidTableRst)
		memset(&rgpro_db.flowEntryValidBits[0], 0, sizeof(rgpro_db.flowEntryValidBits));


	// synchronize reset ddr memory block
	memset(&rgpro_db.ddrMemBlock, 0, sizeof(rgpro_db.ddrMemBlock));

	return SUCCESS;
}

uint32 _rtk_rg_flowEntryValidBit_set(uint8 isValid, uint32 entryIdx)
{
	uint32 validBits = rgpro_db.flowEntryValidBits[entryIdx>>5];
	validBits &= ~(1 << (entryIdx&0x1f));
	validBits |= (isValid << (entryIdx&0x1f));
	rgpro_db.flowEntryValidBits[entryIdx>>5] =  validBits;
	
	return SUCCESS;
}

uint32 _rtk_rg_flowEntryValidBit_get(uint32 entryIdx)
{
	return (rgpro_db.flowEntryValidBits[entryIdx>>5]>>(entryIdx&0x1f)) & 0x1;
}


int32 _rtk_rg_flowEntryAvailableIdx_get(u32 baseEntIdx)
{
	u8 i=0, found=FALSE;
	u8 isValid = FALSE;
	u8 way;
	rtk_rg_asic_fbMode_t fbMode;
	rtk_rg_asic_path1_entry_t flowData;

    	//ASSERT_EQ(rtk_rg_asic_fbModeCtrl_get(FB_MODE_FB_MOD, &mode), RT_ERR_RG_OK);
    	fbMode = rgpro_db.fbMode;
	if(fbMode == FB_MODE_4K) way = 4;
	else way = 1;
	
	for(i=0; i<way; i++){
		// driver need to handle valid/invalid entry in local memory
		if(fbMode == FB_MODE_4K){
			//SRAM mode: get valid information from valid table in memory.
			isValid = _rtk_rg_flowEntryValidBit_get(baseEntIdx);
		}else{
			//DDR mode: get valid information from flow entry in memory.
			ASSERT_EQ(rtk_rg_asic_flowPath1_get(baseEntIdx, &flowData), SUCCESS);
			isValid = flowData.valid;
		}
		//DEBUG("entry idx = %d, valid value = %d", baseEntIdx, isValid);
		if(isValid == FALSE){
			found = TRUE;
			break;
		}
		baseEntIdx++;
	}

	if(!found){
		if((fbMode == FB_MODE_4K)){
			// search TCAM SRAM
			baseEntIdx = RTL9607B_TABLESIZE_FLOWSRAM;
			for(i=0; i<RTL9607B_TABLESIZE_FLOWTCAM; i++){
				isValid = _rtk_rg_flowEntryValidBit_get(baseEntIdx);
				if(isValid == 0){
					found = TRUE;
					break;
				}
				baseEntIdx++;
			}
		}
	}
	DEBUG("Search avaliable entry: %s (%d)", found?"Found":"Not found", baseEntIdx);
	if(!found)
		return FAILED;
	else
		return baseEntIdx;
}

uint32 _rtk_rg_flowEntryWriteToDDR(uint32 entryIdx, void *pFlowData)
{
	// Note: reg.FBA32==0, memory align 4 bytes. (Now 28 bytes per entry)
	//		reg.FBA32==1, memory align 32 bytes.
	int memOffset = (entryIdx << 5);

	if(rgpro_db.ddrBusAlign32==DISABLED)
		memOffset -= (entryIdx << 2);		//entryIdx * sizeof(rtk_rg_asic_path1_entry_t)
	
	if(rgpro_db.ddrMemBase==NULL){
		WARNING("DDR mode memory block was not initialized yet.");
		return FAILED;
	}
	
	memcpy(rgpro_db.ddrMemBase+memOffset, pFlowData, sizeof(rtk_rg_asic_path1_entry_t));

	return SUCCESS;
}

uint32 _rtk_rg_flowEntryReadFromDDR(uint32 entryIdx, void *pFlowData)
{
	// Note: reg.FBA32==0, memory align 4 bytes. (Now 28 bytes per entry)
	//		reg.FBA32==1, memory align 32 bytes.
	int memOffset = (entryIdx << 5);		//entryIdx * sizeof(rtk_rg_asic_path1_entry_t)

	if(rgpro_db.ddrBusAlign32==DISABLED)
		memOffset  -= (entryIdx << 2);
	
	if(rgpro_db.ddrMemBase==NULL){
		WARNING("DDR mode memory block was not initialized yet.");
		return FAILED;
	}
	
	memcpy(pFlowData, rgpro_db.ddrMemBase+memOffset, sizeof(rtk_rg_asic_path1_entry_t));

	return SUCCESS;
}

uint32 _rtk_rg_flowEntryNum_get(void)
{	
	rtk_rg_asic_fbMode_t fbMode = FB_MODE_4K;

	//rtk_rg_asic_fbModeCtrl_get(FB_MODE_FB_MOD, &fbMode);
	fbMode = rgpro_db.fbMode;
	
	//  4K: 2<<1 * 1024 entries
	//  8K: 2<<2 * 1024 entries
	// 16K: 2<<3 * 1024 entries
	// 32K: 2<<4 * 1024 entries
	return ((2 << (fbMode + 1)) << 10);
}

static uint32 _rtk_rg_flowHashPreProcessPort(uint16 port, uint32 cf_ptn){

	uint32 shiftdir = (cf_ptn >> 19) & 0x1;
	uint32 shiftbits = (cf_ptn >> 16) & 0x7;
	uint32 xoroperatedvalue = cf_ptn & 0xffff;
	uint32 port_tmp = 0;
	//DEBUG("Hash - preprocess: shift dir: %d, bits %d, xor value = 0x%x", shiftdir, shiftbits, xoroperatedvalue);
	if(shiftdir){	// shift left
		port_tmp = ((port << shiftbits) & 0xffff) | (port >> (16 - shiftbits));
	}else{		// shift right
		port_tmp = ((port << (16 - shiftbits)) & 0xffff) | (port >> shiftbits);
	}
	//DEBUG("Hash - preprocess: 0x%x ^ 0x%x = 0x%x", port_tmp, xoroperatedvalue, (port_tmp ^ xoroperatedvalue));
	return (port_tmp ^ xoroperatedvalue) & 0xffff;	// sport, dport: (16 bits)

}

static uint32 _rtk_rg_flowHashPreProcessIP(uint32 ip, uint32 cf_ptn){
	uint32 shiftdir = (cf_ptn >> 23) & 0x1;
	uint32 shiftbits = (cf_ptn >> 20) & 0x7;
	uint32 xoroperatedvalue = cf_ptn & 0xfffff;
	uint32 msb_12bits = ip & 0xfff00000;
	uint32 lsb_20bits = ip & 0x000fffff;
	uint32 ip_tmp = 0;
	ip &= 0xfffff;

	if(shiftdir){	// shift left
		ip_tmp = ((lsb_20bits << shiftbits) & 0xfffff) | (ip >> (20 - lsb_20bits));
	}else{		// shift right
		ip_tmp = ((lsb_20bits << (20 - shiftbits)) & 0xfffff) | (lsb_20bits>> shiftbits);
	}

	return (msb_12bits |( (ip_tmp ^ xoroperatedvalue) & 0xfffff));	// sip, dip: (msb12bits + 20 bits)

}

uint32 _rtk_rg_flowHashPath34ExtraItem_get(void *pFlowData, uint16 igrSVID, uint16 igrCVID)
{
	u32 extraItem = 0;
	rtk_rg_asic_path3_entry_t *pP3Data = pFlowData;
	u8 isMulticast = FALSE;
	rtk_enable_t enabled = DISABLED;
	
	if(pP3Data->in_ipv4_or_ipv6 == 1){
		/* IPv6 */
		isMulticast = (pP3Data->in_dst_ipv6_addr_hash& FLOW_V6HASHADDR_MC_BIT)?TRUE:FALSE;
	}else{
		/* IPv4 */
		if((pP3Data->in_dst_ipv4_addr > FLOW_V4ADDR_MC_LO_BOUND) && (pP3Data->in_dst_ipv4_addr < FLOW_V4ADDR_MC_UP_BOUND))
			isMulticast = TRUE;
	}

	if(isMulticast){
		ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH34_MC_SKIP_SVID, &enabled), RT_ERR_RG_OK);
		if(!enabled) extraItem |= (igrSVID<<12); 
		else extraItem &= 0x000fff;
		
		ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH34_MC_SKIP_CVID, &enabled), RT_ERR_RG_OK);
		if(!enabled) extraItem |= igrCVID;
		else extraItem &= 0xfff000;
	}else{
		ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH34_UCBC_SKIP_SVID, &enabled), RT_ERR_RG_OK);
		if(!enabled) extraItem |= (igrSVID<<12); 
		else extraItem &= 0x000fff;
		
		ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH34_UCBC_SKIP_CVID, &enabled), RT_ERR_RG_OK);
		if(!enabled) extraItem |= igrCVID;
		else extraItem &= 0xfff000;
	}
	/* Extraitem: Consider L4 protocol only for path 3/4/5 */
	extraItem = (pP3Data->in_l4proto<<23) ^ extraItem;
	
	return extraItem;
}


uint32 _rtk_rg_flowHashPath5ExtraItem_get(void *pFlowData, uint16 igrSVID, uint16 igrCVID)
{
	u32 extraItem = 0;
	rtk_rg_asic_path5_entry_t *pP5Data = pFlowData;
	rtk_enable_t enabled = DISABLED;

	ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH5_SKIP_SVID, &enabled), RT_ERR_RG_OK);
	if(!enabled) extraItem |= (igrSVID<<12); 
	else extraItem &= 0x000fff;
			
	ASSERT_EQ(rtk_rg_asic_globalState_get(FB_GLOBAL_PATH5_SKIP_CVID, &enabled), RT_ERR_RG_OK);
	if(!enabled) extraItem |= igrCVID;
	else extraItem &= 0xfff000;

	/* Extraitem: Consider L4 protocol only for path 3/4/5 */
	extraItem = (pP5Data->in_l4proto<<23) ^ extraItem;

	return extraItem;
}

/* _rtk_rg_flowHashIndexStep1_get()
	return value: HashIdx
		- 4K mode: (10 bits hash index)<<2 (4-way, need to search entry from (HashIdx<<2+0) to (HashIdx<<2+3) );
		- 8K/16K/32K mode: 13bits/14bits/15bits entry index (1-way, directly mapping)						*/
uint32 _rtk_rg_flowHashIndexStep1_get(uint16 param1, uint16 param2, uint32 param3, uint32 param4, uint32 extraItem){
	uint32 sum1=0, sum2=0, sum=0, sum_nk=0, hashIdx=0;
	uint32 sport, dport, sip, dip;
	rtk_rg_asic_fbMode_t fbMode;
	uint32 preHashPtn;
	
	//ASSERT_EQ(rtk_rg_asic_fbModeCtrl_get(FB_MODE_FB_MOD, &fbMode), SUCCESS);
	fbMode = rgpro_db.fbMode;

	ASSERT_EQ(rtk_rg_asic_preHashPtn_get(FB_PREHASH_PTN_SPORT, &preHashPtn), SUCCESS);
	sport = _rtk_rg_flowHashPreProcessPort(param1, preHashPtn);
	ASSERT_EQ(rtk_rg_asic_preHashPtn_get(FB_PREHASH_PTN_DPORT, &preHashPtn), SUCCESS);
	dport = _rtk_rg_flowHashPreProcessPort(param2, preHashPtn);
	ASSERT_EQ(rtk_rg_asic_preHashPtn_get(FB_PREHASH_PTN_SIP, &preHashPtn), SUCCESS);
	sip = _rtk_rg_flowHashPreProcessIP(param3, preHashPtn);
	ASSERT_EQ(rtk_rg_asic_preHashPtn_get(FB_PREHASH_PTN_DIP, &preHashPtn), SUCCESS);
	dip = _rtk_rg_flowHashPreProcessIP(param4, preHashPtn);

	sum1 = ((sip&0xfffff)  + (sip>>20) + (dip&0xfffff) + (dip>>20) + sport + dport) & 0x7fffff;		// sum1[22:0]
	sum2 = ((sum1&0xfffff) + (sum1>>20)) & 0x1fffff;						// sum2[20:0]
	sum	  = ((sum2&0xfffff) + (sum>>20)) & 0x1fffff;						// sum[20:0]
	switch(fbMode)
	{
		case FB_MODE_4K:
			// 4k mode: 4-way (10 bits index)
			sum_nk = ((sum&0x3ff) + ((sum>>10)&0x3ff) + ((sum>>20)&0x1))&0x3ff;		// sum_4k[9:0]
			hashIdx = sum_nk ^ (extraItem&0x3ff) ^ ((extraItem>>10)&0x3ff) ^ ((extraItem>>20)&0xf);
			hashIdx = hashIdx<<2;												// Get base entry index
			break;
		case FB_MODE_8K:
			// 8k mode: 1-way (13 bits index)
			sum1 = (sum&0x1fff) + ((sum>>13)&0xff);
			sum2 = (sum1&0xfff) ^ ((sum1>>12)&0x1);
			sum_nk = (sum1&0x1000) | (sum2&0xfff);							// sum_8k[12:0]
			hashIdx = sum_nk ^ (extraItem&0x1fff) ^ ((extraItem>>13)&0x7ff);
			break;
		case FB_MODE_16K:
			// 16k mode: 1-way (14 bits index)
			sum1 = (sum&0x3fff) + ((sum>>14)&0x7f);
			sum2 = (sum1&0xfff) ^ ((sum1>>12)&0x3);
			sum_nk = (sum1&0x3000) | (sum2&0xfff);							// sum_8k[13:0]
			hashIdx = sum_nk ^ (extraItem&0x3fff) ^ ((extraItem>>13)&0x3ff);
			break;
		case FB_MODE_32K:
			// 32k mode: 1-way (15 bits index)
			sum1 = (sum&0x7fff) + ((sum>>13)&0x3f);
			sum2 = (sum1&0xfff) ^ ((sum1>>12)&0x7);
			sum_nk = (sum1&0x7000) | (sum2&0xfff);							// sum_8k[14:0]
			hashIdx = sum_nk ^ (extraItem&0x7fff) ^ ((extraItem>>13)&0x1ff);
			break;
	}

	DEBUG("[FLOWHASH] index=%d, fbMode=%d, params: [0x%x,0x%x,0x%x,0x%x], extra:0x%x", hashIdx, fbMode, param1, param2, param3, param4, extraItem);
	return hashIdx;
}

uint32 _rtk_rg_flowHashIndexStep2_get(uint32 step1Idx)
{
	uint32 hashidx = 0;
	uint32 mask = 0x7E03;	// Hid_s2[14:0] = {~hid[14:10], ~hid[9], hid[8:2], ~hid[1:0]}	0x7E03= 111_1110_0000_0011
	rtk_rg_asic_fbMode_t fbMode;
	
	//ASSERT_EQ(rtk_rg_asic_fbModeCtrl_get(FB_MODE_FB_MOD, &fbMode), SUCCESS);
	fbMode = rgpro_db.fbMode;
	switch(fbMode)
	{
		case FB_MODE_4K:
			// 4k mode: 4-way (10 bits index)
			hashidx = step1Idx >> 2;			// shift back to 10 bits
			mask = mask & 0x3ff;				// Hid_s2[9:0] = { ~hid[9], hid[8:2], ~hid[1:0]} => 10 bits mask
			hashidx = hashidx ^ mask;
			hashidx = hashidx << 2;			// shift to 12 bits 4 way entry index
			break;
		case FB_MODE_8K:
			// 8k mode: 1-way (13 bits index)
			mask = mask & 0x1fff;
			hashidx = step1Idx ^ mask;			
			break;
		case FB_MODE_16K:
			// 16k mode: 1-way (14 bits index)
			mask = mask & 0x3fff;
			hashidx = step1Idx ^ mask;
			break;
		case FB_MODE_32K:
			// 32k mode: 1-way (15 bits index)
			mask = mask & 0x7fff;
			hashidx = step1Idx ^ mask;
			break;	
	}
	
	DEBUG("[FLOWHASH] index=%d (Step2), fbMode=%d", hashidx, fbMode);
	return hashidx;
}

uint32 _rtk_rg_flowHashIPv6DstAddr_get(uint8 ipDes[16])
{
	/* Dst hashidx = {MC_bit, v6hsh[30:0]} */
	uint32 hashIdx = ntohl((*(uint32*)&ipDes[0])) ^ ntohl((*(uint32*)&ipDes[4])) ^ ntohl((*(uint32*)&ipDes[8])) ^ ntohl((*(uint32*)&ipDes[12]));
	hashIdx = (hashIdx >> 31) ^ (hashIdx & 0x7fffffff);
	/* Set MC bit to 1 if ipv6 address is started with ffxx*/
	if(ipDes[0] == 0xff)
		hashIdx |= (1<<31);
	//DEBUG("hashIdx = 0x%x", hashIdx);
	return hashIdx;
}

uint32 _rtk_rg_flowHashIPv6SrcAddr_get(uint8 ipDes[16])
{
	/* Dst hashidx = {MC_bit, v6hsh[30:0]} */
	uint32 hashIdx = ntohl((*(uint32*)&ipDes[0])) ^ ntohl((*(uint32*)&ipDes[4])) ^ ntohl((*(uint32*)&ipDes[8])) ^ ntohl((*(uint32*)&ipDes[12]));

	//DEBUG("hashIdx = 0x%x", hashIdx);
	return hashIdx;
}

uint32 _rtk_rg_fbMode_set(rtk_rg_asic_fbMode_t fbMode)
{
	uint32 numFlowEntry = 0;
	uint32 memSize = 0;
	void *ddrMemBase = NULL;

	ASSERT_EQ(rtk_rg_asic_fbModeCtrl_set(FB_MODE_FB_MOD, fbMode), SUCCESS);
	rgpro_db.fbMode = fbMode;

	// reset all tables!
	ASSERT_EQ(rtk_rg_asic_table_reset(FB_RST_ALL), SUCCESS);

	numFlowEntry = _rtk_rg_flowEntryNum_get();
#ifndef CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC		
	memSize = sizeof(rgpro_db.ddrMemBlock) - 1023;				//maximun allocation but ignore alignment
#else
	// Note: Assume reg.FBA32==0, memory align 4 bytes not 32 bytes.
	memSize = (numFlowEntry << 5) - (numFlowEntry << 2);	//numFlowEntry * sizeof(rtk_rg_asic_path1_entry_t) = numFlowEntry * 28 bytes
#endif

	if(rgpro_db.ddrMemAlloc != NULL){
#ifndef CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC		
		rgpro_db.ddrMemAlloc = NULL;
#else
	#ifdef __KERNEL__	
		kfree(rgpro_db.ddrMemAlloc);
		rgpro_db.ddrMemAlloc = NULL;
	#else
		rtlglue_free(rgpro_db.ddrMemAlloc);
	#endif
#endif
	}
	if(fbMode != FB_MODE_4K){
		/* Allocate memory and set base address to configure cache controller */
		ddrMemBase = _rtk_rg_memoryAlignAlloc(1024, memSize);
		if(ddrMemBase == NULL)
			return RT_ERR_RG_FAILED;
	
		TRACE("Config DDR mode %d: flow table alloc mem %d bytes @ %p", fbMode, memSize, ddrMemBase);

		ASSERT_EQ(rtk_rg_asic_ccMemAddr_set(&ddrMemBase), SUCCESS);
		rgpro_db.ddrMemBase = ddrMemBase;
	}else
	{
		TRACE("Config DDR mode %d: reset ddr memory block", fbMode, memSize, ddrMemBase);
		
		ASSERT_EQ(rtk_rg_asic_ccMemAddr_set(&ddrMemBase), SUCCESS);
		rgpro_db.ddrMemBase = NULL;
	}
		
	return 0;
}
rtk_rg_asic_fbMode_t _rtk_rg_fbMode_get(void)
{
	return rgpro_db.fbMode;
}

uint32 _rtk_rg_init_rgProDB()
{
	uint8 u8Sta = 0;
	rtk_enable_t enableSta = DISABLED;
	DEBUG("Exec RG PRO DB initilization!");
	
    	ASSERT_EQ(rtk_rg_asic_fbModeCtrl_get(FB_MODE_FB_MOD, &u8Sta), RT_ERR_RG_OK);
	rgpro_db.fbMode = u8Sta;
    	ASSERT_EQ(rtk_rg_asic_ccGlobalState_get(FB_CC_GLOBAL_BUS_ALIGN, &enableSta), RT_ERR_RG_OK);
	rgpro_db.ddrBusAlign32 = enableSta;
	
	rgpro_db.ddrMemAlloc = NULL;
	rgpro_db.ddrMemBase = NULL;
	memset(&rgpro_db.ddrMemBlock, 0, sizeof(rgpro_db.ddrMemBlock));
	
#if !defined(CONFIG_APOLLO_PRO_MODEL) && !defined(CONFIG_APOLLOPRO_FPGA)
	memset(&rgpro_db.flowEntryValidBits, 0, sizeof(rgpro_db.flowEntryValidBits));
	rgpro_db.ignoreFlowValidTableRst = FALSE;
#endif

	return SUCCESS;
}


#endif

