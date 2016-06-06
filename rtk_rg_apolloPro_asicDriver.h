/*
 * Copyright (C) 2012 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
*/

#ifndef __RTK_RG_ASIC_APOLLOPROFB_H__
#define __RTK_RG_ASIC_APOLLOPROFB_H__


/*
 * Include Files
 */
#include <common/rt_type.h>
#include <common/rt_error.h>
#include <rtk_rg_struct.h>
#include <rtk_rg_cpuReason.h>

/*
 * Symbol Definition
 */

//#define RTL9602C_L34_HSB_WORD 10

// Table Size 
#define RTL9607B_TABLESIZE_FLOWSRAM 	4096
#define RTL9607B_TABLESIZE_FLOWTCAM 	64
#define RTL9607B_TABLESIZE_FLOWTAG 	RTL9607B_TABLESIZE_FLOWSRAM
#define RTL9607B_TABLESIZE_CAMTAG 	RTL9607B_TABLESIZE_FLOWTCAM
#define RTL9607B_TABLESIZE_INTF 		16
#define RTL9607B_TABLESIZE_MACIND 	256
#define RTL9607B_TABLESIZE_ETHERTYPE 	16
#define RTL9607B_TABLESIZE_EXTPORT 	32
#define RTL9607B_TABLESIZE_SHAREMTR 	32
#define RTL9607B_TABLESIZE_EXTMBR 		32
#define RTL9607B_TABLESIZE_SP2C 		64


#define RTL9607B_EXTRATAG_LISTMIN 	1
#define RTL9607B_EXTRATAG_LISTMAX 	7
#define RTL9607B_EXTRATAG_ACTIONS 	8


#define LUT_BC_IDX	0xffe

#define FLOW_V6HASHADDR_MC_BIT 0x80000000
#define FLOW_V4ADDR_MC_LO_BOUND 0xe0000000
#define FLOW_V4ADDR_MC_UP_BOUND 0xf0000000

#define RTK_RG_MAC_PORT_ALLCPUMASK (1<<RTK_RG_MAC_PORT_SLAVECPU)|(1<<RTK_RG_MAC_PORT_MASTERCPU_CORE0)|(1<<RTK_RG_MAC_PORT_MASTERCPU_CORE1)

#define CTTLINIT								7	// cache entry time-to-live
#define TRAPPRI_FLOWMISSINIT				1	// trap priority when flow miss 
#define DDRMODE_VALIDTBL_STARTPOSITION	512	// shared with traffic table

/*
 * Data Declaration
 */

/* flow-based global state */
typedef enum rtk_rg_asic_globalStateType_s
{
    	FB_GLOBAL_STATE_START = 0,
	FB_GLOBAL_TTL_1 = FB_GLOBAL_STATE_START,
	FB_GLOBAL_TRAP_TCP_SYN_FIN_REST,
	FB_GLOBAL_TRAP_TCP_SYN_ACK,
	FB_GLOBAL_TRAP_FRAGMENT,
	FB_GLOBAL_L3_CS_CHK,
	FB_GLOBAL_L4_CS_CHK,
	FB_GLOBAL_PATH12_SKIP_CVID,
	FB_GLOBAL_PATH34_UCBC_SKIP_CVID,
	FB_GLOBAL_PATH34_MC_SKIP_CVID,
	FB_GLOBAL_PATH5_SKIP_CVID,
	FB_GLOBAL_PATH6_SKIP_CVID,
	FB_GLOBAL_PATH12_SKIP_SVID,
	FB_GLOBAL_PATH34_UCBC_SKIP_SVID,
	FB_GLOBAL_PATH34_MC_SKIP_SVID,
	FB_GLOBAL_PATH5_SKIP_SVID,
	FB_GLOBAL_PATH6_SKIP_SVID,
	FB_GLOBAL_L2_FLOW_LOOKUP_BY_MAC,
	FB_GLOBAL_CMP_TOS,
	FB_GLOBAL_STATE_END
}rtk_rg_asic_globalStateType_t;

/* flow-based mode control */
typedef enum rtk_rg_asic_fbModeCtrl_s
{
	FB_MODE_RST_VLD,
	FB_MODE_RST_TRF,
	FB_MODE_FB_MOD,
}rtk_rg_asic_fbModeCtrl_t;

typedef enum rtk_rg_asic_fbMode_s 
{
	FB_MODE_4K = 0,
	FB_MODE_8K = 1,
	FB_MODE_16K = 2,
	FB_MODE_32K = 3,
}rtk_rg_asic_fbMode_t;

typedef enum rtk_rg_asic_preHashPtn_s
{
	FB_PREHASH_PTN_SPORT = 0,
	FB_PREHASH_PTN_DPORT,
	FB_PREHASH_PTN_SIP,
	FB_PREHASH_PTN_DIP,
	FB_PREHASH_PTN_END,
}rtk_rg_asic_preHashPtn_t;

/* flow-based dual header used registers */
typedef enum rtk_rg_asic_dualHdrInfo_s
{
    	FB_DUALHDR_GRESEQ = 0,
    	FB_DUALHDR_GREACK,
	FB_DUALHDR_OUTER_IPV4ID,
	FB_DUALHDR_END,
}rtk_rg_asic_dualHdrInfo_t;

/* flow-based forwarding action */
typedef enum rtk_rg_asic_forwardAction_s
{
   	FB_ACTION_FORWARD = 0,
	FB_ACTION_TRAP2CPU,
	FB_ACTION_DROP,
	FB_ACTION_END
}rtk_rg_asic_forwardAction_t;

/* flow-based pppoe action */
typedef enum rtk_rg_asic_pppoeAct_e
{
	FB_PPPOE_ACT_KEEP  = 0,
	FB_PPPOE_ACT_ADD,
	FB_PPPOE_ACT_MODIFY,
	FB_PPPOE_ACT_REMOVE,
    	FB_PPPOE_ACT_END
} rtk_rg_asic_pppoeAct_t;

typedef enum rtk_rg_asic_extraTagAct_type_e
{
	FB_EXTG_ACTBIT_NOACTION=0,
	FB_EXTG_ACTBIT_1,
	FB_EXTG_ACTBIT_2,
	FB_EXTG_ACTBIT_3,
	FB_EXTG_ACTBIT_4,
	FB_EXTG_ACTBIT_5,
	FB_EXTG_ACTBIT_6,
}rtk_rg_asic_extraTagAct_type_t;

/* flow-based table type for reset */
typedef enum rtk_rg_asic_resetTableType_s
{
	FB_RST_IF_TBL = 1<<0,
	FB_RST_ETHER_TYPE = 1<<1,
	FB_RST_EXT_PMASK_TYPE = 1<<3,
	FB_RST_FLOW_TBL = 1<<8,
	FB_RST_CAM_TBL = 1<<9,
	FB_RST_MAC_INDEX_TBL = 1<<10,
	FB_RST_TCAM_TBL = 1<<12,
	FB_RST_TRAFFIC_TBL,
	FB_RST_VLAN_TBL,
	FB_RST_VALID_TBL,
	FB_RST_ALL,
	FB_RST_VIR_MAC,
	FB_RST_END
}rtk_rg_asic_resetTableType_t;

typedef enum rtk_rg_asic_cacheCtrl_sysCmdCode_s
{
	FB_CC_CMD_INVFLOW = 1,
	FB_CC_CMD_ADDFLOW,
	FB_CC_CMD_ULCKALL,
	FB_CC_CMD_ULCKFLOW,
	FB_CC_CMD_READFLOW,
	FB_CC_CMD_UPDFLOW,
	FB_CC_CMD_CHKALL,
	FB_CC_CMD_END
}rtk_rg_asic_cacheCtrl_sysCmdCode_t;

typedef enum rtk_rg_asic_cacheCtrl_faultRsn_s
{
	FB_CC_FAULT_NONE=0,
	FB_CC_FAULT_CMD,
	FB_CC_FAULT_GRANT,
	FB_CC_FAULT_DATA,
	FB_CC_FAULT_UNKNOWN,
}rtk_rg_asic_cacheCtrl_faultRsn_t;

typedef enum rtk_rg_asic_cacheCtrl_ctrllerSta_s
{
	FB_CC_STA_INIT=0,
	FB_CC_STA_IDLE,
	FB_CC_STA_LOOKUP,
	FB_CC_STA_EXECMD,
}rtk_rg_asic_cacheCtrl_ctrllerSta_t;

typedef enum rtk_rg_asic_cacheCtrl_globalCtrlType_s
{
	FB_CC_GLOBAL_STATE_START = 0,
	FB_CC_GLOBAL_CACHE_EN = FB_CC_GLOBAL_STATE_START,
	FB_CC_GLOBAL_CAM_EN,
	FB_CC_GLOBAL_FLOW_VALID_EN,
	FB_CC_GLOBAL_CAM_TO_CACHE_EN,
	FB_CC_GLOBAL_BUS_ALIGN,
	FB_CC_GLOBAL_TAG_CHK,
	FB_CC_GLOBAL_END,
}rtk_rg_asic_cacheCtrl_globalCtrlType_t;

typedef enum rtk_rg_asic_cacheCtrl_systemCmd_s
{
	FB_CC_SYSTEMCMD_INVALIDATE,
	FB_CC_SYSTEMCMD_ADD,
	FB_CC_SYSTEMCMD_UNLOCKALL,
	FB_CC_SYSTEMCMD_UNLOCKFLW,
	FB_CC_SYSTEMCMD_READ,
	FB_CC_SYSTEMCMD_UPDATE,
	FB_CC_SYSTEMCMD_CHECKALL,
}rtk_rg_asic_cacheCtrl_systemCmd_t;

/* the return code of system command INVALIDATE */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeInv_s
{
	FB_CC_INVSTA_SUCCESS_CACHE 				= 0x00,
	FB_CC_INVSTA_SUCCESS_CAM 				= 0x01,
	FB_CC_INVSTA_WARNING_BOTHHIT 			= 0x20,
	FB_CC_INVSTA_WARNING_BOTHMISS 			= 0x40,
}rtk_rg_asic_cacheCtrl_rtnCodeInv_t;

/* the return code of system command ADD */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeAdd_s
{
	FB_CC_ADDSTA_SUCCESS_CACHE 				= 0x00,
	FB_CC_ADDSTA_SUCCESS_CAM 				= 0x01,
	FB_CC_ADDSTA_SUCCESS_LOWPRI 			= 0x02,			// Flow is not added into cache or cam because of lower priority.
	FB_CC_ADDSTA_WARNING_BOTHHIT 			= 0x20,
	FB_CC_ADDSTA_WARNING_CACHEEXIST 		= 0x40,		// do replace
	FB_CC_ADDSTA_WARNING_CAMEXIST 			= 0x41,		// do replace
	FB_CC_ADDSTA_WARNING_PARAMERR 			= 0x80,
}rtk_rg_asic_cacheCtrl_rtnCodeAdd_t;

/* the return code of system command UNLOCKALL */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeUlckAll_s
{
	FB_CC_ULCKALLSTA_SUCCESS_DONE 			= 0x00,
	FB_CC_ULCKALLSTA_WARNING_ERR 			= 0x80,
}rtk_rg_asic_cacheCtrl_rtnCodeUlckAll_t;

/* the return code of system command UNLOCKFLW */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeUlck_s
{
	FB_CC_ULCKSTA_SUCCESS_CACHE 			= 0x00,
	FB_CC_ULCKSTA_SUCCESS_CAM 				= 0x01,
	FB_CC_ULCKSTA_WARNING_BOTHHIT 			= 0x20,
	FB_CC_ULCKSTA_WARNING_BOTHMISS 		= 0x40,
	FB_CC_ULCKSTA_WARNING_CACHEUNLCK 		= 0x41,
	FB_CC_ULCKSTA_WARNING_CAMUNLCK 		= 0x42,
}rtk_rg_asic_cacheCtrl_rtnCodeUlck_t;

/* the return code of system command READ */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeRead_s
{
	FB_CC_READSTA_SUCCESS_CACHE 			= 0x00,
	FB_CC_READSTA_SUCCESS_CAM 				= 0x01,
	FB_CC_READSTA_WARNING_BOTHHIT 			= 0x20,			// read cache only
	FB_CC_READSTA_WARNING_BOTHMISS 		= 0x40,
}rtk_rg_asic_cacheCtrl_rtnCodeRead_t;

/* the return code of system command UPDATE */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeUpd_s
{
	FB_CC_UPDSTA_SUCCESS_INVFLW_TO_CACHE 	= 0x00,	// invalid flow in main memory
	FB_CC_UPDSTA_SUCCESS_INVFLW_TO_CAM 	= 0x01,
	FB_CC_UPDSTA_SUCCESS_INVFLW_BOTHMISS 	= 0x02,
	FB_CC_UPDSTA_SUCCESS_VALFLW_TO_CACHE 	= 0x03,	// valid flow in main memory
	FB_CC_UPDSTA_SUCCESS_VALFLW_TO_CAM 	= 0x04,
	FB_CC_UPDSTA_SUCCESS_VALFLW_LOWPRI 	= 0x05,		// flow is not added into cache or cam because of lower priority
	
	FB_CC_UPDSTA_WARNING_VALFLW_BOTHHIT 	= 0x20,
	FB_CC_UPDSTA_WARNING_INVFLW_BOTHHIT 	= 0x21,
}rtk_rg_asic_cacheCtrl_rtnCodeUpd_t;

/* the return code of system command CHECKALL */
typedef enum rtk_rg_asic_cacheCtrl_rtnCodeChkAll_s
{
	FB_CC_CHKALLSTA_SUCCESS_DONE 			= 0x00,
	FB_CC_CHKALLSTA_WARNING_ERR 			= 0x80,
}rtk_rg_asic_cacheCtrl_rtnCodeChkAll_t;

typedef enum rtk_rg_asic_inprotocol_type_e
{
	FB_INPROTOCOL_ETHTBL_0 = 0,
	FB_INPROTOCOL_ETHTBL_1,
	FB_INPROTOCOL_ETHTBL_2,
	FB_INPROTOCOL_ETHTBL_3,
	FB_INPROTOCOL_ETHTBL_4,
	FB_INPROTOCOL_ETHTBL_5,
	FB_INPROTOCOL_ETHTBL_6,
	FB_INPROTOCOL_RESERVED,
	FB_INPROTOCOL_INNER_IPV4 = 8,
	FB_INPROTOCOL_INNER_IPV6 = 9,
	FB_INPROTOCOL_OUTER_0800 = 10,
	FB_INPROTOCOL_OUTER_8863 = 11,
	FB_INPROTOCOL_OUTER_8864 = 12,
	FB_INPROTOCOL_OUTER_86DD = 13,
	FB_INPROTOCOL_OUTER_PPPOE = 14,
	FB_INPROTOCOL_ALL_ACCEPT = 15,
}rtk_rg_asic_inprotocol_type_t;

typedef enum rtk_rg_asic_pkt_type_e
{
	FB_PKTTYPE_RESERVED = 0,
	FB_PKTTYPE_MC = 1,
	FB_PKTTYPE_UC = 2,
	FB_PKTTYPE_BC = 3,
}rtk_rg_asic_pkt_type_t;


/* L34 HSB data */
typedef struct rtk_rg_asic_hsb_entry_s
{	
	uint32 OUT_DPORT:16;
	uint32 OUT_SPORT:16;
	uint32 OUT_L4_PTC:1;
	uint32 OUT_L4_TYPE:1;
	uint32 OUT_IPMF:1;
	uint32 OUT_TOS:8;
	uint32 L2_LEN_DIFF:10;
	uint32 GRE_SEQ:32;
	uint32 L2TP_ID:16;
	uint32 L2TP_SESSION:16;
	uint32 L2TP:1;
	uint32 GRE:1;
	uint32 UDP_NOCS:1;
	uint32 TCP_FLAG:4;
	uint32 DPORT:16;
	uint32 SPORT:16;
	uint32 L4_CSOK:1;
	uint32 L4_PTC:1;
	uint32 L4_TYPE:1;
	uint32 DIP_HSH:32;
	uint32 SIP_HSH:32;
	uint32 DIP_V4:32;
	uint32 SIP_V4:32;
	uint32 IPV6_OUT:1;
	uint32 L3_CSOK:1;
	uint32 IPMF:1;
	uint32 IP_OPTION:1;
	uint32 TTL_ST:1;
	uint32 TOS:8;
	uint32 IPV4_6:1;
	uint32 IP:1;
	uint32 DUAL_FAIL:1;
	uint32 DUAL_HDR:1;
	uint32 L2_LEN:14;
	uint32 SA_IDX:12;
	uint32 DA_IDX:12;
	uint32 PPPOE_SID:16;
	uint32 SVLAN_ID:12;
	uint32 CVLAN_ID:12;
	uint32 PPPOE_IF:1;
	uint32 STAG_IF:1;
	uint32 CTAG_IF:1;
	uint32 ETH_TYPE:16;
	uint32 STM_IDX:7;
	uint32 SPA_EXT:3;
	uint32 SPA:4;
	uint32 GMAC_CHK:1;
	uint32 PKT_TYPE:2;
}rtk_rg_asic_hsb_entry_t;

/* L34 HSA data */
typedef struct rtk_rg_asic_hsa_entry_s
{
	/* Non Path5 */
	uint32 S2_SMAC_T:1;
	uint32 S2_EXTP_MASK:18;
	uint32 S2_PMASK:11;
	uint32 S2_EX_TAG_IDX:3;
	uint32 S2_PP_SID:16;
	uint32 S2_PP_ACT:1;
	uint32 S2_O_IF_IDX:4;
	uint32 S2_USER_PRI:3;
	uint32 S2_USER_PRI_ACT:1;
	uint32 S2_DSCP:6;
	uint32 S2_DSCP_ACT:1;
	uint32 S2_SPRI:3;
	uint32 S2_SVID:12;
	uint32 S2_EGS_SVID_ACT:1;
	uint32 S2_SPRI_ACT:1;
	uint32 S2_SVID_ACT:1;
	uint32 S2_STAG_ACT:1;
	uint32 S2_CPRI:3;
	uint32 S2_CVID:12;
	uint32 S2_EGS_CVID_ACT:1;
	uint32 S2_CPRI_ACT:1;
	uint32 S2_CVID_ACT:1;
	uint32 S2_CTAG_ACT:1;
	uint32 S2_VID2C_ACT:1;
	uint32 S2_ACT:1;

	/* Path5 */
	uint32 S1_L4_CS:16;
	uint32 S1_L3_CS:16;
	uint32 S1_PORT:16;
	uint32 S1_IP:32;
	uint32 S1_L4_DIR:1;
	uint32 S1_L4_ACT:1;

	/* Shared Data for Path1~5 */
	uint32 S1_P5:1;
	uint32 S1_SMAC_T:1;
	uint32 S1_EXTP_MASK:18;
	uint32 S1_PMASK:11;
	uint32 S1_EX_TAG_IDX:3;
	uint32 S1_PP_SID:16;
	uint32 S1_PP_ACT:1;
	uint32 S1_O_IF_IDX:4;
	uint32 S1_USER_PRI:3;
	uint32 S1_USER_PRI_ACT:1;
	uint32 S1_DSCP:6;
	uint32 S1_DSCP_ACT:1;
	uint32 S1_SPRI:3;
	uint32 S1_SVID:12;
	uint32 S1_EGS_SVID_ACT:1;
	uint32 S1_SPRI_ACT:1;
	uint32 S1_SVID_ACT:1;
	uint32 S1_STAG_ACT:1;
	uint32 S1_CPRI:3;
	uint32 S1_CVID:12;
	uint32 S1_EGS_CVID_ACT:1;
	uint32 S1_CPRI_ACT:1;
	uint32 S1_CVID_ACT:1;
	uint32 S1_CTAG_ACT:1;
	uint32 S1_VID2C_ACT:1;
	uint32 HSA_DMAC_IDX:12;
	uint32 HSA_DMAC_T:1;
	uint32 HSA_STREAM_IDX:7;
	uint32 HSA_STREAM_ACT:1;
	uint32 HSA_UC_LUT_LUP:1;
	uint32 HSA_I_IF_IDX:4;
	uint32 HSA_PKT_TYPE:2;
	uint32 HSA_HIT_DUAL:1;
	uint32 HSA_ACT_DROP:1;
	uint32 HSA_ACT_TRAP:1;
	uint32 HSA_ACT:2;

	/* Trap/Drop */
	uint32 HSA_HID:15;
	uint32 HSA_HID_VLD:1;
	uint32 HSA_PRI:3;
	uint32 HSA_PRI_EN:1;
	uint32 HSA_RSN:6;
}rtk_rg_asic_hsa_entry_t;


typedef enum rtk_rg_out_egress_port_to_vid_act_e
{
	FB_ACT_NONE = 0,
	FB_ACT_SP2C = 1,
	FB_ACT_SP2S = 2,
	FB_ACT_CP2C = 3,
	FB_ACT_XP2X_MAX,
}rtk_rg_out_egress_port_to_vid_act_t;


/* flow-based table - for path 1 */
typedef struct rtk_rg_asic_path1_entry_s
{
	/* word 0 */
	uint32 valid:1;
	uint32 out_dmac_trans:1;
	uint32 in_path:2;
	uint32 in_intf_idx:4;
	uint32 in_out_stream_idx_check_act:1;
	uint32 in_multiple_act:1;
	uint32 out_share_meter_act:1;
	uint32 out_share_meter_idx:5;
	uint32 in_spa_check:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 out_intf_idx:4;
	uint32 in_tos:8;
	/* word 1 */
	uint32 in_protocol:4;
	uint32 in_smac_lut_idx:12;
	uint32 reserved1:4;
	uint32 in_dmac_lut_idx:12;
	/* word 2 */
	uint32 reserved2:4;
	uint32 in_svlan_id:12;
	uint32 reserved3:4;
	uint32 in_cvlan_id:12;
	/* word 3 */
	uint32 reserved4:4;
	uint32 in_spa:4;
	uint32 reserved5:5;
	uint32 in_ext_spa:3;
	uint32 in_pppoe_sid:16;
	/* word 4 */
	uint32 out_dmac_idx:8;
	uint32 out_svid_format_act:1;
	uint32 out_user_priority:3;
	uint32 out_cvid_format_act:1;
	uint32 out_extra_tag_index:3;
	uint32 out_ext_portmask_idx:5;
	uint32 out_portmask:11;
	/* word 5 */
	uint32 out_spri_format_act:1;
	uint32 out_spri:3;
	uint32 out_svlan_id:12;
	uint32 out_cpri_format_act:1;
	uint32 out_cpri:3;
	uint32 out_cvlan_id:12;
	/* word 6 */
	uint32 in_pppoe_sid_check:1;
	uint32 in_out_stream_idx:7;
	uint32 out_multiple_act:1;
	uint32 out_dscp_act:1;
	uint32 out_dscp:6;
	uint32 out_drop:1;
	uint32 out_egress_cvid_act:1;
	uint32 out_egress_svid_act:1;
	uint32 out_ctag_format_act:1;
	uint32 out_stag_format_act:1;
	uint32 out_user_pri_act:1;
	uint32 out_egress_port_to_vid_act:2;  //b'00:none  b'01:SP2C  b'10:SP2S   b'11:CP2C  refto rtk_rg_out_egress_port_to_vid_act_t
	uint32 out_smac_trans:1;
	uint32 out_uc_lut_lookup:1;
	uint32 reserved6:1;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path1_entry_t;

/* flow-based table - for path 2  */
typedef struct rtk_rg_asic_path2_entry_s
{
	/* word 0 */
   	uint32 valid:1;
	uint32 reserved1:1;
	uint32 in_path:2;
	uint32 reserved2:4;
	uint32 in_stream_idx_check:1;
	uint32 in_multiple_act:1;
	uint32 reserved3:6;
	uint32 in_spa_check:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 out_intf_idx:4;
	uint32 in_tos:8;
	/* word 1 */
	uint32 in_protocol:4;
	uint32 in_smac_lut_idx:12;
	uint32 reserved4:4;
	uint32 in_dmac_lut_idx:12;
	/* word 2 */
	uint32 reserved5:4;
	uint32 in_svlan_id:12;
	uint32 reserved6:4;
	uint32 in_cvlan_id:12;
	/* word 3 */
	uint32 reserved7:4;
	uint32 in_spa:4;
	uint32 reserved8:5;
	uint32 in_ext_spa:3;
	uint32 in_pppoe_sid:16;
	/* word 4 */
	uint32 reserved9:8;
	uint32 out_svid_format_act:1;
	uint32 out_user_priority:3;
	uint32 out_cvid_format_act:1;
	uint32 out_extra_tag_index:3;
	uint32 out_ext_portmask_idx:5;
	uint32 out_portmask:11;
	/* word 5 */
	uint32 out_spri_format_act:1;
	uint32 out_spri:3;
	uint32 out_svlan_id:12;
	uint32 out_cpri_format_act:1;
	uint32 out_cpri:3;
	uint32 out_cvlan_id:12;
	/* word 6 */
	uint32 in_pppoe_sid_check:1;
	uint32 in_stream_idx:7;
	uint32 reserved10:1;
	uint32 out_dscp_act:1;
	uint32 out_dscp:6;
	uint32 reserved11:1;
	uint32 out_egress_cvid_act:1;
	uint32 out_egress_svid_act:1;
	uint32 out_ctag_format_act:1;
	uint32 out_stag_format_act:1;
	uint32 out_user_pri_act:1;
	uint32 out_egress_port_to_vid_act:2;//b'00:none  b'01:SP2C  b'10:SP2S   b'11:CP2C  refto rtk_rg_out_egress_port_to_vid_act_t
	uint32 out_smac_trans:1;
	uint32 reserved12:2;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path2_entry_t;

/* flow-based table - for path 3 */
typedef struct rtk_rg_asic_path3_entry_s
{
	/* word 0 */
	uint32 valid:1;
	uint32 out_dmac_trans:1;
	uint32 in_path:2;
	uint32 in_intf_idx:4;
	uint32 out_stream_idx_act:1;
	uint32 in_multiple_act:1;
	uint32 out_share_meter_act:1;
	uint32 out_share_meter_idx:5;
	uint32 in_ipv4_or_ipv6:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 out_intf_idx:4;
	uint32 in_tos:8;
	/* word 1 */
	union
	{
		uint32 in_src_ipv4_addr:32;
		uint32 in_src_ipv6_addr_hash:32;
	};
	/* word 2 */
	union
	{
		uint32 in_dst_ipv4_addr:32;
		uint32 in_dst_ipv6_addr_hash:32;
	};
	/* word 3 */
	uint32 in_l4_src_port:16;
	uint32 in_l4_dst_port:16;
	/* word 4 */
	uint32 out_dmac_idx:8;
	uint32 out_svid_format_act:1;
	uint32 out_user_priority:3;
	uint32 out_cvid_format_act:1;
	uint32 out_extra_tag_index:3;
	uint32 out_ext_portmask_idx:5;
	uint32 out_portmask:11;
	/* word 5 */
	uint32 out_spri_format_act:1;
	uint32 out_spri:3;
	uint32 out_svlan_id:12;
	uint32 out_cpri_format_act:1;
	uint32 out_cpri:3;
	uint32 out_cvlan_id:12;
	/* word 6 */
	uint32 in_pppoe_sid_check:1;
	uint32 out_stream_idx:7;
	uint32 out_multiple_act:1;
	uint32 out_dscp_act:1;
	uint32 out_dscp:6;
	uint32 out_drop:1;
	uint32 out_egress_cvid_act:1;
	uint32 out_egress_svid_act:1;
	uint32 out_ctag_format_act:1;
	uint32 out_stag_format_act:1;
	uint32 out_user_pri_act:1;
	uint32 out_egress_port_to_vid_act:2;//b'00:none  b'01:SP2C  b'10:SP2S   b'11:CP2C  refto rtk_rg_out_egress_port_to_vid_act_t
	uint32 out_smac_trans:1;
	uint32 out_uc_lut_lookup:1;
	uint32 in_l4proto:1;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path3_entry_t;

/* flow-based table - for path 4 */
typedef struct rtk_rg_asic_path4_entry_s
{
	/* word 0 */
	uint32 valid:1;
	uint32 reserved1:1;
	uint32 in_path:2;
	uint32 in_intf_idx:4;
	uint32 reserved2:1;
	uint32 in_multiple_act:1;
	uint32 reserved3:6;
	uint32 in_ipv4_or_ipv6:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 out_intf_idx:4;
	uint32 in_tos:8;
	/* word 1 */
	union
	{
		uint32 in_src_ipv4_addr:32;
		uint32 in_src_ipv6_addr_hash:32;
	};
	/* word 2 */
	union
	{
		uint32 in_dst_ipv4_addr:32;
		uint32 in_dst_ipv6_addr_hash:32;
	};
	/* word 3 */
	uint32 in_l4_src_port:16;
	uint32 in_l4_dst_port:16;
	/* word 4 */
	uint32 reserved4:8;
	uint32 out_svid_format_act:1;
	uint32 out_user_priority:3;
	uint32 out_cvid_format_act:1;
	uint32 out_extra_tag_index:3;
	uint32 out_ext_portmask_idx:5;
	uint32 out_portmask:11;
	/* word 5 */
	uint32 out_spri_format_act:1;
	uint32 out_spri:3;
	uint32 out_svlan_id:12;
	uint32 out_cpri_format_act:1;
	uint32 out_cpri:3;
	uint32 out_cvlan_id:12;
	/* word 6 */
	uint32 in_pppoe_sid_check:1;
	uint32 reserved5:8;
	uint32 out_dscp_act:1;
	uint32 out_dscp:6;
	uint32 reserved6:1;
	uint32 out_egress_cvid_act:1;
	uint32 out_egress_svid_act:1;
	uint32 out_ctag_format_act:1;
	uint32 out_stag_format_act:1;
	uint32 out_user_pri_act:1;
	uint32 out_egress_port_to_vid_act:2;//b'00:none  b'01:SP2C  b'10:SP2S   b'11:CP2C  refto rtk_rg_out_egress_port_to_vid_act_t
	uint32 out_smac_trans:1;
	uint32 reserved7:1;
	uint32 in_l4proto:1;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path4_entry_t;

/* flow-based table - unicast l34 routing/napt, for path 5  */
typedef struct rtk_rg_asic_path5_entry_s
{
	/* word 0 */
	uint32 valid:1;
	uint32 reserved1:1;
	uint32 in_path:2;
	uint32 in_intf_idx:4;
	uint32 out_stream_idx_act:1;
	uint32 reserved2:1;
	uint32 out_share_meter_act:1;
	uint32 out_share_meter_idx:5;
	uint32 in_ipv4_or_ipv6:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 out_intf_idx:4;
	uint32 in_tos:8;
	/* word 1 */
	union
	{
		uint32 in_src_ipv4_addr:32;
		uint32 in_src_ipv6_addr_hash:32;
	};
	/* word 2 */
	union
	{
		uint32 in_dst_ipv4_addr:32;		//routing/napt mode
		uint32 in_dst_ipv6_addr_hash:32; 	//routing/napt mode
		uint32 out_dst_ipv4_addr:32;		//napt-r mode
	};
	/* word 3 */
	uint32 in_l4_src_port:16;
	uint32 in_l4_dst_port:16;
	/* word 4 */
	uint32 out_dmac_idx:8;
	uint32 out_svid_format_act:1;
	uint32 out_user_priority:3;
	uint32 out_cvid_format_act:1;
	uint32 out_extra_tag_index:3;
	uint32 out_l4_port:16;
	/* word 5 */
	uint32 out_spri_format_act:1;
	uint32 out_spri:3;
	uint32 out_svlan_id:12;
	uint32 out_cpri_format_act:1;
	uint32 out_cpri:3;
	uint32 out_cvlan_id:12;
	/* word 6 */
	uint32 out_l4_direction:1;				// 0:inbound, 1:outbound
	uint32 out_stream_idx:7;
	uint32 out_l4_act:1;
	uint32 out_dscp_act:1;
	uint32 out_dscp:6;
	uint32 out_drop:1;
	uint32 out_egress_cvid_act:1;
	uint32 out_egress_svid_act:1;
	uint32 out_ctag_format_act:1;
	uint32 out_stag_format_act:1;
	uint32 out_user_pri_act:1;
	uint32 out_egress_port_to_vid_act:2;//b'00:none  b'01:SP2C  b'10:SP2S   b'11:CP2C  refto rtk_rg_out_egress_port_to_vid_act_t
	uint32 reserved3:2;
	uint32 in_l4proto:1;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path5_entry_t;

/* flow-based table - dual header, for path 6  */
typedef struct rtk_rg_asic_path6_entry_s
{
	uint32 valid:1;
	uint32 reserved1:1;
	uint32 in_path:2;
	uint32 in_intf_idx:4;
	uint32 in_l4_src_port_check:1;
	uint32 in_l4_dst_port_check:1;
	uint32 in_l2tp_tunnel_id_check:1;
	uint32 in_l2tp_session_id_check:1;
	uint32 in_src_mac_check:1;
	uint32 in_dst_mac_check:1;
	uint32 in_src_ip_check:1;
	uint32 in_dst_ip_check:1;
	uint32 in_ipv4_or_ipv6:1;
	uint32 in_ctagif:1;
	uint32 in_stagif:1;
	uint32 in_pppoeif:1;
	uint32 reserved2:4;
	uint32 in_tos:8;	
    union
	{
		uint32 in_src_ipv4_addr:32;
		uint32 in_src_ipv6_addr_hash:32;
	};
	union
	{
		uint32 in_dst_ipv4_addr:32;
		uint32 in_dst_ipv6_addr_hash:32;
	};
	uint32 in_l4_src_port:16;
	uint32 in_l4_dst_port:16;
	uint32 in_protocol:4;
	uint32 reserved3:4;
	uint32 in_smac_lut_idx:12;
	uint32 in_dmac_lut_idx:12;
	uint32 in_l2tp_tunnel_id:16;
	union
	{
		uint16 in_gre_call_id:16;	   	//pptp mode
		uint16 in_l2tp_session_id:16; 	//l2tp mode
	};
	uint32 reserved4:16;
	uint32 out_drop:1;
	uint32 reserved5:9;
	uint32 in_gre_call_id_check:1;
	uint32 in_dscp_check:1;
	uint32 lock:1;
}rtk_rg_asic_path6_entry_t;

/* flow Tag table for DDR mode */
typedef struct rtk_rg_asic_flowTag_entry_s
{
	uint32 hashIdxMsb:3;
	uint32 TTL:4;
}rtk_rg_asic_flowTag_entry_t;

/* cam Tag table for DDR mode */
typedef struct rtk_rg_asic_camTag_entry_s
{
	uint32 hsahIdx:15;
	uint32 lock:1;
	uint32 valid:1;
}rtk_rg_asic_camTag_entry_t;

/* interface table */
typedef struct rtk_rg_asic_netif_entry_s
{
	uint8 valid;
	rtk_mac_t gateway_mac_addr;
	ipaddr_t gateway_ipv4_addr;
	uint16 intf_mtu;
	uint8 intf_mtu_check;
	uint16 out_pppoe_sid;
	uint8 out_pppoe_act;
	uint8 deny_ipv4;
	uint8 deny_ipv6;
	rtk_rg_asic_forwardAction_t ingress_action;
	rtk_rg_asic_forwardAction_t egress_action;
	rtk_portmask_t allow_ingress_portmask;
	rtk_portmask_t allow_ingress_ext_portmask;
}rtk_rg_asic_netif_entry_t;

/* interface table */
typedef struct rtk_rg_asic_netifMib_entry_s
{
	uint32 in_intf_uc_packet_cnt;
	uint64 in_intf_uc_byte_cnt;
	uint32 in_intf_mc_packet_cnt;
	uint64 in_intf_mc_byte_cnt;
	uint32 in_intf_bc_packet_cnt;
	uint64 in_intf_bc_byte_cnt;
	uint32 out_intf_uc_packet_cnt;
	uint64 out_intf_uc_byte_cnt;
	uint32 out_intf_mc_packet_cnt;
	uint64 out_intf_mc_byte_cnt;
	uint32 out_intf_bc_packet_cnt;
	uint64 out_intf_bc_byte_cnt;
}rtk_rg_asic_netifMib_entry_t;


/* mac address indirect access table */
typedef struct rtk_rg_asic_indirectMac_entry_s
{
	uint32 l2_idx:12;
}rtk_rg_asic_indirectMac_entry_t;

/* extension port mask table */
typedef struct rtk_rg_asic_extPortMask_entry_s
{
	uint32 FB_EXT_PMASK:18;
}rtk_rg_asic_extPortMask_entry_t;

/* ether-type table */
typedef struct rtk_rg_asic_etherType_entry_s
{
    uint16 ethertype;
}rtk_rg_asic_etherType_entry_t;

/* extra tag action */
typedef struct rtk_rg_asic_extraTagAction_s
{
	union{
		struct{							// Update Ethertype & MTU
 			uint32 act_bit: 3;
			uint32 ethertype: 16;
			uint32 reserve0: 9;
			uint32 ethertype_trans: 1;
			uint32 reserve1: 1;
		}type1;
		struct{							// Inser extra tag to specific location
 			uint32 act_bit: 3;
			uint32 reserve0: 8;
			uint32 length: 8;
			uint32 src_addr_offset: 9;		// MUST be 4-bytes alignment
			uint32 reserve1: 2;
		}type2;
		struct{							// Update Outer IP header length
 			uint32 act_bit: 3;
			uint32 pkt_buff_offset: 8;		// replaced offset
			uint32 length: 8;
			uint32 value: 9;
			uint32 operation: 2;			// 0:+; 1:-; 2:*; 3:/;
		}type3;
		struct{							// Update GRE seg or IPv4 ID
 			uint32 act_bit: 3;
			uint32 pkt_buff_offset: 8;
			uint32 seq_ack_reg_idx: 4;
			uint32 reserve0: 3;
			uint32 data_src_type: 1;		// 0: GRE seq/ack 1:IP Identification
			uint32 reserve1: 11;
		}type4;
		struct{							// Caculate outer L3 header checksum (L3 checksum offload)
 			uint32 act_bit: 3;
			uint32 pkt_buff_offset: 8;
			uint32 reserve0: 19;
		}type5;
		struct{							// Caculate outer L4 header checksum (L4 checksum offload)
 			uint32 act_bit: 3;
			uint32 pkt_buff_offset: 8;
			uint32 reserve0: 19;
		}type6;	
	}act;	
}rtk_rg_asic_extraTagAction_t;

typedef struct rtk_rg_asic_cacheCtrlCmd_e
{
	uint32 hashID:15;
	uint32 reserved1:1;
	uint32 cBit:1;
	uint32 aBit:1;
	uint32 vBit:1;
	uint32 pBit:1;
	uint32 fBit:1;
	uint32 reserved2:3;
	uint32 cmdCode:7;
	uint32 reqExec:1;
}rtk_rg_asic_cacheCtrlCmd_t;

typedef struct rtk_rg_asic_cacheState_s
{
	uint8 ccBusy:1;
	rtk_rg_asic_cacheCtrl_ctrllerSta_t ccCurState:2;
	rtk_rg_asic_cacheCtrl_faultRsn_t ccFaultStatus:3;
	union{
		rtk_rg_asic_cacheCtrl_rtnCodeInv_t invRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeAdd_t addRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeUlckAll_t ulckallRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeUlck_t ulckRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeRead_t readRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeUpd_t updRtn;
		rtk_rg_asic_cacheCtrl_rtnCodeChkAll_t chkRtn;
		uint32 cmdRtn;
	}ccCmdRtnCode;	
}rtk_rg_asic_cacheState_t;

typedef struct rtk_rg_asic_cacheReadSta_e
{
	uint8 TTL;
	uint8 readFromCache;
	uint8 readFromCam;
}rtk_rg_asic_cacheReadSta_t;

/*
 * Symbol Definition
 */


/*
 * Function Declaration
 */

extern rtk_rg_err_code_t rtk_rg_asic_hsbaMode_set(rtk_l34_hsba_mode_t hsbaMode);

extern rtk_rg_err_code_t rtk_rg_asic_hsbaMode_get(rtk_l34_hsba_mode_t *pHsbaMode);

extern rtk_rg_err_code_t rtk_rg_asic_hsbData_get(rtk_rg_asic_hsb_entry_t *pHsbData);

extern rtk_rg_err_code_t rtk_rg_asic_hsaData_get(rtk_rg_asic_hsa_entry_t *pHsaData);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath_del(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath1_add(uint32 *idx, rtk_rg_asic_path1_entry_t *pP1Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath1_set(uint32 idx, rtk_rg_asic_path1_entry_t *pP1Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath1_get(uint32 idx, rtk_rg_asic_path1_entry_t *pP1Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath2_add(uint32 *idx, rtk_rg_asic_path2_entry_t *pP2Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath2_set(uint32 idx, rtk_rg_asic_path2_entry_t *pP2Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath2_get(uint32 idx, rtk_rg_asic_path2_entry_t *pP2Data);
	
extern rtk_rg_err_code_t rtk_rg_asic_flowPath3_add(uint32 *idx, rtk_rg_asic_path3_entry_t *pP3Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath3_set(uint32 idx, rtk_rg_asic_path3_entry_t *pP3Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath3_get(uint32 idx, rtk_rg_asic_path3_entry_t *pP3Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath4_add(uint32 *idx, rtk_rg_asic_path4_entry_t *pP4Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath4_set(uint32 idx, rtk_rg_asic_path4_entry_t *pP4Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath4_get(uint32 idx, rtk_rg_asic_path4_entry_t *pP4Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath5_add(uint32 *idx, rtk_rg_asic_path5_entry_t *pP5Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath5_set(uint32 idx, rtk_rg_asic_path5_entry_t *pP5Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath5_get(uint32 idx, rtk_rg_asic_path5_entry_t *pP5Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath6_add(uint32 *idx, rtk_rg_asic_path6_entry_t *pP6Data, uint16 igrSVID, uint16 igrCVID);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath6_set(uint32 idx, rtk_rg_asic_path6_entry_t *pP6Data);

extern rtk_rg_err_code_t rtk_rg_asic_flowPath6_get(uint32 idx, rtk_rg_asic_path6_entry_t *pP6Data);

extern rtk_rg_err_code_t rtk_rg_asic_netifTable_add(uint32 idx, rtk_rg_asic_netif_entry_t *pNetifEntry);

extern rtk_rg_err_code_t rtk_rg_asic_netifTable_del(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_netifTable_get(uint32 idx, rtk_rg_asic_netif_entry_t *pNetifEntry);

extern rtk_rg_err_code_t rtk_rg_asic_netifMib_get(uint32 idx, rtk_rg_asic_netifMib_entry_t *pNetifMibEntry);

extern rtk_rg_err_code_t rtk_rg_asic_netifMib_reset(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_indirectMacTable_add(uint32 idx, rtk_rg_asic_indirectMac_entry_t *pIndirectMacEntry);

extern rtk_rg_err_code_t rtk_rg_asic_indirectMacTable_del(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_indirectMacTable_get(uint32 idx, rtk_rg_asic_indirectMac_entry_t *pIndirectMacEntry);

extern rtk_rg_err_code_t rtk_rg_asic_extPortMaskTable_add(uint32 idx, rtk_rg_asic_extPortMask_entry_t *pExtPMaskEntry);

extern rtk_rg_err_code_t rtk_rg_asic_extPortMaskTable_del(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_extPortMaskTable_get(uint32 idx, rtk_rg_asic_extPortMask_entry_t *pExtPMaskEntry);

extern rtk_rg_err_code_t rtk_rg_asic_etherTypeTable_add(uint32 idx, rtk_rg_asic_etherType_entry_t *pEtherTypeEntry);

extern rtk_rg_err_code_t rtk_rg_asic_etherTypeTable_del(uint32 idx);

extern rtk_rg_err_code_t rtk_rg_asic_etherTypeTable_get(uint32 idx, rtk_rg_asic_etherType_entry_t *pEtherTypeEntry);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagAction_add(uint32 actionList, uint32 actionIdx, rtk_rg_asic_extraTagAction_t *pExtraTagAction);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagAction_del(uint32 actionList, uint32 actionIdx);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagAction_get(uint32 actionList, uint32 actionIdx, rtk_rg_asic_extraTagAction_t *pExtraTagAction);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagContentBuffer_set(uint32 offset, uint32 len, char *pContentBuffer);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagContentBuffer_get(uint32 offset, uint32 len, char *pContentBuffer);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagInsertHdrLen_set(uint32 actionList, uint32 len);

extern rtk_rg_err_code_t rtk_rg_asic_extraTagInsertHdrLen_get(uint32 actionList, uint32 *len);

extern rtk_rg_err_code_t rtk_rg_asic_flowTrfIndicator_get(uint32 idx, rtk_enable_t *pFlowIndicator);

extern rtk_rg_err_code_t rtk_rg_asic_flowTraffic_get(uint32 *validSet, uint32 *flowTrafficSet);

extern rtk_rg_err_code_t rtk_rg_asic_netifTrfIndicator_get(uint32 idx, rtk_enable_t *pNetifIndicator);

extern rtk_rg_err_code_t rtk_rg_asic_netifTraffic_get(uint32 *value);

extern rtk_rg_err_code_t rtk_rg_asic_unmatchedCpuPriority_set(uint32 priority);

extern rtk_rg_err_code_t rtk_rg_asic_unmatchedCpuPriority_get(uint32 *pPriority);

extern rtk_rg_err_code_t rtk_rg_asic_trapCpuPriority_set(rtk_enable_t state, uint32 priority);

extern rtk_rg_err_code_t rtk_rg_asic_trapCpuPriority_get(rtk_enable_t *pState, uint32 *pPriority);

extern rtk_rg_err_code_t rtk_rg_asic_spaUnmatchAction_set(rtk_rg_asic_forwardAction_t action);

extern rtk_rg_err_code_t rtk_rg_asic_spaUnmatchAction_get(rtk_rg_asic_forwardAction_t *pAction);

extern rtk_rg_err_code_t rtk_rg_asic_globalState_set(rtk_rg_asic_globalStateType_t stateType, rtk_enable_t state);

extern rtk_rg_err_code_t rtk_rg_asic_globalState_get(rtk_rg_asic_globalStateType_t stateType, rtk_enable_t *pState);

extern rtk_rg_err_code_t rtk_rg_asic_fbModeCtrl_set(rtk_rg_asic_fbModeCtrl_t ctrlType, uint8 state);

extern rtk_rg_err_code_t rtk_rg_asic_fbModeCtrl_get(rtk_rg_asic_fbModeCtrl_t ctrlType, uint8 *pState);

extern rtk_rg_err_code_t rtk_rg_asic_preHashPtn_set(rtk_rg_asic_preHashPtn_t ptnType, uint32 code);

extern rtk_rg_err_code_t rtk_rg_asic_preHashPtn_get(rtk_rg_asic_preHashPtn_t ptnType, uint32 *pCode);

extern rtk_rg_err_code_t rtk_rg_asic_dualHdrInfo_set(rtk_rg_asic_dualHdrInfo_t target, uint8 intfIdx, uint32 value);

extern rtk_rg_err_code_t rtk_rg_asic_dualHdrInfo_get(rtk_rg_asic_dualHdrInfo_t target, uint8 intfIdx, uint32 *value);

extern rtk_rg_err_code_t rtk_rg_asic_shareMeter_set(uint32 index, uint32 rate, rtk_enable_t ifgInclude);

extern rtk_rg_err_code_t rtk_rg_asic_shareMeter_get(uint32 index, uint32 *pRate , rtk_enable_t *pIfgInclude);

extern rtk_rg_err_code_t rtk_rg_asic_shareMeterBucket_set(uint32 index, uint32 bucketSize);

extern rtk_rg_err_code_t rtk_rg_asic_shareMeterBucket_get(uint32 index, uint32 *pBucketSize);

extern rtk_rg_err_code_t rtk_rg_asic_table_reset(rtk_rg_asic_resetTableType_t type);

extern rtk_rg_err_code_t rtk_rg_asic_ccMemAddr_set(void **pMemBase);

extern rtk_rg_err_code_t rtk_rg_asic_ccMemAddr_get(void **pMemBase);

extern rtk_rg_err_code_t rtk_rg_asic_ccInvalidFlow_cmd(rtk_enable_t invValid, uint32 entryIdx);

extern rtk_rg_err_code_t rtk_rg_asic_ccAddFlow_cmd(rtk_enable_t forceAdd, rtk_enable_t highPri, rtk_enable_t rstValid, rtk_enable_t addToCAM, rtk_enable_t addToCache, uint32 entryIdx, uint32 *pFlowData);

extern rtk_rg_err_code_t rtk_rg_asic_ccUnlockAll_cmd(rtk_enable_t unlockCAM, rtk_enable_t unlockCache);

extern rtk_rg_err_code_t rtk_rg_asic_ccUnlockFlow_cmd(uint32 entryIdx);

extern rtk_rg_err_code_t rtk_rg_asic_ccReadFlow_cmd(uint32 entryIdx, uint32 *pFlowData, rtk_rg_asic_cacheReadSta_t *cReadSta);

extern rtk_rg_err_code_t rtk_rg_asic_ccUpdateFlow_cmd(rtk_enable_t forceAdd, rtk_enable_t addToCAM, rtk_enable_t addToCache, uint32 entryIdx);

extern rtk_rg_err_code_t rtk_rg_asic_ccCheckAll_cmd(rtk_enable_t pktStatistic, rtk_enable_t tblStatistic);

extern rtk_rg_err_code_t rtk_rg_asic_ccSysCmdState_get(rtk_rg_asic_cacheState_t *pCCState);

extern rtk_rg_err_code_t rtk_rg_asic_ccPktStatistic_get(uint32 *pCompleteMissRate, uint32 *pCacheMissRate, uint32 *pMissCycle);

extern rtk_rg_err_code_t rtk_rg_asic_ccTblStatisticValidCnt_get(uint32 *pCacheCnt, uint32 *pCamCnt);

extern rtk_rg_err_code_t rtk_rg_asic_ccTblStatisticLockCnt_get(uint32 *pCacheCnt, uint32 *pCamCnt);

extern rtk_rg_err_code_t rtk_rg_asic_ccGlobalState_set(rtk_rg_asic_cacheCtrl_globalCtrlType_t stateType, rtk_enable_t state);

extern rtk_rg_err_code_t rtk_rg_asic_ccGlobalState_get(rtk_rg_asic_cacheCtrl_globalCtrlType_t stateType, rtk_enable_t *pState);

extern rtk_rg_err_code_t rtk_rg_asic_ccFlowTagTTLThrd_set(uint32 initValue);

extern rtk_rg_err_code_t rtk_rg_asic_ccFlowTagTTLThrd_get(uint32 *pInitValue);

extern rtk_rg_err_code_t rtk_rg_asic_flowValidBit_get(uint32 idx, rtk_enable_t *pFlowValidBit);

extern rtk_rg_err_code_t rtk_rg_asic_flowTagTable_set(uint32 index, rtk_rg_asic_flowTag_entry_t *pTagEntry);

extern rtk_rg_err_code_t rtk_rg_asic_flowTagTable_get(uint32 index, rtk_rg_asic_flowTag_entry_t *pTagEntry);

extern rtk_rg_err_code_t rtk_rg_asic_camTraffic_get(uint64 *pCamTrfBits);

extern rtk_rg_err_code_t rtk_rg_asic_camTagTable_set(uint32 index, rtk_rg_asic_camTag_entry_t *pTagEntry);

extern rtk_rg_err_code_t rtk_rg_asic_camTagTable_get(uint32 index, rtk_rg_asic_camTag_entry_t *pTagEntry);

extern rtk_rg_err_code_t rtk_rg_asic_fb_init(void);


#endif /* __RTK_RG_ASIC_APOLLOPROFB_H__ */

