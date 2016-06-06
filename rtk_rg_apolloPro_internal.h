#ifndef __RTK_RG_APOLLOPRO_INTERNAL_H__
#define __RTK_RG_APOLLOPRO_INTERNAL_H__

#include <common/rt_type.h>
#include <common/rt_error.h>
#include <rtk_rg_struct.h>
#include <rtk_rg_apolloPro_asicDriver.h>


#ifdef CONFIG_RTL9607B_SERIES

#ifndef SUCCESS
#define SUCCESS	0
#endif
#ifndef FAILED
#define FAILED	-1
#endif


#ifndef IS_CLASSD_ADDR
#define IS_CLASSD_ADDR(ipv4addr)				((((uint32)(ipv4addr)) & 0xf0000000) == 0xe0000000)
#endif

#define IS_V6FLOWHASH_MCADDR(ipv6hashaddr)		((((uint32)(ipv6hashaddr)) & FLOW_V6HASHADDR_MC_BIT) == FLOW_V6HASHADDR_MC_BIT)

typedef struct rtk_rg_fbDatabase_s
{
	/* Register status */
	uint8 fbMode;
	uint8 ddrBusAlign32;
	/***************/
	void *ddrMemAlloc;
	void *ddrMemBase;
#ifndef CONFIG_RTL9607B_SERIES_DYNAMIC_MALLOC
	char ddrMemBlock[(32<<15) + 1023];		// maximum occupied memory size: 32 byte align * 32K mode + 1023 (prepare for 1k aligned base address)
#endif
	uint8 ignoreFlowValidTableRst;
	uint32 flowEntryValidBits[(32<<10)>>5];		// maximum valid bits: (32K / 32 bit) words

}rtk_rg_fbDatabase_t;


#define DDRMODE_HASHIDX2CACHEIDX(hashIdx)	hashIdx&(RTL9607B_TABLESIZE_FLOWTAG-1)
#define DDRMODE_HASHIDX2MSB(hashIdx)			hashIdx>>12

uint32 _rtk_rg_flowEntryValidBitIgnoreRst(rtk_enable_t state);
uint32 _rtk_rg_flowEntryValidBit_reset(void);
uint32 _rtk_rg_flowEntryValidBit_set(uint8 isValid, uint32 entryIdx);
uint32 _rtk_rg_flowEntryValidBit_get(uint32 entryIdx);
int32 _rtk_rg_flowEntryAvailableIdx_get(u32 baseEntIdx);
uint32 _rtk_rg_flowEntryWriteToDDR(uint32 entryIdx, void *pFlowData);
uint32 _rtk_rg_flowEntryReadFromDDR(uint32 entryIdx, void *pFlowData);
uint32 _rtk_rg_flowEntryNum_get(void);

uint32 _rtk_rg_flowHashPath34ExtraItem_get(void *pFlowData, uint16 igrSVID, uint16 igrCVID);
uint32 _rtk_rg_flowHashPath5ExtraItem_get(void *pFlowData, uint16 igrSVID, uint16 igrCVID);
uint32 _rtk_rg_flowHashIndexStep1_get(uint16 param1, uint16 param2, uint32 param3, uint32 param4, uint32 extraItem);
uint32 _rtk_rg_flowHashIndexStep2_get(uint32 step1Idx);
uint32 _rtk_rg_flowHashIPv6DstAddr_get(uint8 ipDes[16]);
uint32 _rtk_rg_flowHashIPv6SrcAddr_get(uint8 ipDes[16]);

uint32 _rtk_rg_fbMode_set(rtk_rg_asic_fbMode_t fbMode);
uint32 _rtk_rg_fbMode_get(void);
uint32 _rtk_rg_init_rgProDB(void);

#endif //CONFIG_RTL9607B_SERIES

#endif //__RTK_RG_APOLLOPRO_INTERNAL_H__

