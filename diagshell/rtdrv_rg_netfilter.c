/*Copyright (C) 2009 Realtek Semiconductor Corp.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Purpose : Realtek Switch SDK Rtdrv Netfilter Module.
 *
 * Feature : Realtek Switch SDK Rtdrv Netfilter Module
 *
 */

/*
 * Include Files
 */
#include <asm/uaccess.h>
#include <rtdrv/rtdrv_rg_netfilter.h>
#if defined(CONFIG_RTK_L34_ENABLE) && CONFIG_RTK_L34_ENABLE==1 || defined(CONFIG_XDSL_RG_DIAGSHELL)
static int32
_rg_init_parameterCheck(rtk_rg_initParams_t* init_param){
    rtk_rg_initParams_t null_init_param;
    memset(&null_init_param,0xff,sizeof(rtk_rg_initParams_t));
    //chuck: check the struct init_param has been setting.
    //else, 0xffffffff struct rtk_rg_initParams_t means use default value to init rg

    if(memcmp(init_param,&null_init_param,sizeof(rtk_rg_initParams_t)))
        return RT_ERR_FAILED;//use init_param as parameter
    else
        return RT_ERR_OK;//use NULL as parameter
}
#endif


/* Function Name:
 *      do_rtdrv_set_ctl
 * Description:
 *      This function is called whenever a process tries to do setsockopt
 * Input:
 *      *sk   - network layer representation of sockets
 *      cmd   - ioctl commands
 *      *user - data buffer handled between user and kernel space
 *      len   - data length
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      None
 */
int32 do_rtdrv_rg_set_ctl(struct sock *sk, int cmd, void *user, unsigned int len)
{
    int32                           ret = RT_ERR_FAILED;
    rtdrv_rg_union_t                buf;

    switch(cmd)
    {

#if defined(CONFIG_RTK_L34_ENABLE) && CONFIG_RTK_L34_ENABLE==1 || defined(CONFIG_XDSL_RG_DIAGSHELL)
		/* RG SET API */

		case RTDRV_RG_DHCPREQUEST_SET:
			copy_from_user(&buf.rtdrv_rg_dhcpRequest_set_cfg, user, sizeof(rtdrv_rg_dhcpRequest_set_t));
			ret = rtk_rg_dhcpRequest_set(buf.rtdrv_rg_dhcpRequest_set_cfg.wan_intf_idx);
			break;

		case RTDRV_RG_INTERFACE_DEL:
			copy_from_user(&buf.rtdrv_rg_interface_del_cfg, user, sizeof(rtdrv_rg_interface_del_t));
			ret = rtk_rg_interface_del(buf.rtdrv_rg_interface_del_cfg.lan_or_wan_intf_idx);
			break;

		case RTDRV_RG_SVLANTPID_SET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid_set_cfg, user, sizeof(rtdrv_rg_svlanTpid_set_t));
			ret = rtk_rg_svlanTpid_set(buf.rtdrv_rg_svlanTpid_set_cfg.svlan_tag_id);
			break;

		case RTDRV_RG_SVLANSERVICEPORT_SET:
			copy_from_user(&buf.rtdrv_rg_svlanServicePort_set_cfg, user, sizeof(rtdrv_rg_svlanServicePort_set_t));
			ret = rtk_rg_svlanServicePort_set(buf.rtdrv_rg_svlanServicePort_set_cfg.port, buf.rtdrv_rg_svlanServicePort_set_cfg.enable);
			break;

		case RTDRV_RG_CVLAN_DEL:
			copy_from_user(&buf.rtdrv_rg_cvlan_del_cfg, user, sizeof(rtdrv_rg_cvlan_del_t));
			ret = rtk_rg_cvlan_del(buf.rtdrv_rg_cvlan_del_cfg.cvlan_id);
			break;

		case RTDRV_RG_VLANBINDING_DEL:
			copy_from_user(&buf.rtdrv_rg_vlanBinding_del_cfg, user, sizeof(rtdrv_rg_vlanBinding_del_t));
			ret = rtk_rg_vlanBinding_del(buf.rtdrv_rg_vlanBinding_del_cfg.vlan_binding_idx);
			break;

		case RTDRV_RG_ALGSERVERINLANAPPSIPADDR_DEL:
			copy_from_user(&buf.rtdrv_rg_algServerInLanAppsIpAddr_del_cfg, user, sizeof(rtdrv_rg_algServerInLanAppsIpAddr_del_t));
			ret = rtk_rg_algServerInLanAppsIpAddr_del(buf.rtdrv_rg_algServerInLanAppsIpAddr_del_cfg.delServerMapping);
			break;

		case RTDRV_RG_ALGAPPS_SET:
			copy_from_user(&buf.rtdrv_rg_algApps_set_cfg, user, sizeof(rtdrv_rg_algApps_set_t));
			ret = rtk_rg_algApps_set(buf.rtdrv_rg_algApps_set_cfg.alg_app);
			break;

		case RTDRV_RG_VIRTUALSERVER_DEL:
			copy_from_user(&buf.rtdrv_rg_virtualServer_del_cfg, user, sizeof(rtdrv_rg_virtualServer_del_t));
			ret = rtk_rg_virtualServer_del(buf.rtdrv_rg_virtualServer_del_cfg.virtual_server_idx);
			break;

		case RTDRV_RG_ACLFILTERANDQOS_DEL:
			copy_from_user(&buf.rtdrv_rg_aclFilterAndQos_del_cfg, user, sizeof(rtdrv_rg_aclFilterAndQos_del_t));
			ret = rtk_rg_aclFilterAndQos_del(buf.rtdrv_rg_aclFilterAndQos_del_cfg.acl_filter_idx);
			break;

		case RTDRV_RG_NAPTFILTERANDQOS_DEL:
			copy_from_user(&buf.rtdrv_rg_naptFilterAndQos_del_cfg, user, sizeof(rtdrv_rg_naptFilterAndQos_del_t));
			ret = rtk_rg_naptFilterAndQos_del(buf.rtdrv_rg_naptFilterAndQos_del_cfg.index);
			break;

		case RTDRV_RG_MACFILTER_DEL:
			copy_from_user(&buf.rtdrv_rg_macFilter_del_cfg, user, sizeof(rtdrv_rg_macFilter_del_t));
			ret = rtk_rg_macFilter_del(buf.rtdrv_rg_macFilter_del_cfg.mac_filter_idx);
			break;

		case RTDRV_RG_URLFILTERSTRING_DEL:
			copy_from_user(&buf.rtdrv_rg_urlFilterString_del_cfg, user, sizeof(rtdrv_rg_urlFilterString_del_t));
			ret = rtk_rg_urlFilterString_del(buf.rtdrv_rg_urlFilterString_del_cfg.url_idx);
			break;

		case RTDRV_RG_UPNPCONNECTION_DEL:
			copy_from_user(&buf.rtdrv_rg_upnpConnection_del_cfg, user, sizeof(rtdrv_rg_upnpConnection_del_t));
			ret = rtk_rg_upnpConnection_del(buf.rtdrv_rg_upnpConnection_del_cfg.upnp_idx);
			break;

		case RTDRV_RG_NAPTCONNECTION_DEL:
			copy_from_user(&buf.rtdrv_rg_naptConnection_del_cfg, user, sizeof(rtdrv_rg_naptConnection_del_t));
			ret = rtk_rg_naptConnection_del(buf.rtdrv_rg_naptConnection_del_cfg.flow_idx);
			break;

		case RTDRV_RG_MULTICASTFLOW_DEL:
			copy_from_user(&buf.rtdrv_rg_multicastFlow_del_cfg, user, sizeof(rtdrv_rg_multicastFlow_del_t));
			ret = rtk_rg_multicastFlow_del(buf.rtdrv_rg_multicastFlow_del_cfg.flow_idx);
			break;

		case RTDRV_RG_MACENTRY_DEL:
			copy_from_user(&buf.rtdrv_rg_macEntry_del_cfg, user, sizeof(rtdrv_rg_macEntry_del_t));
			ret = rtk_rg_macEntry_del(buf.rtdrv_rg_macEntry_del_cfg.entry_idx);
			break;

		case RTDRV_RG_ARPENTRY_DEL:
			copy_from_user(&buf.rtdrv_rg_arpEntry_del_cfg, user, sizeof(rtdrv_rg_arpEntry_del_t));
			ret = rtk_rg_arpEntry_del(buf.rtdrv_rg_arpEntry_del_cfg.arp_entry_idx);
			break;

		case RTDRV_RG_NEIGHBORENTRY_DEL:
			copy_from_user(&buf.rtdrv_rg_neighborEntry_del_cfg, user, sizeof(rtdrv_rg_neighborEntry_del_t));
			ret = rtk_rg_neighborEntry_del(buf.rtdrv_rg_neighborEntry_del_cfg.neighbor_idx);
			break;

		case RTDRV_RG_ACCESSWANLIMIT_SET:
			copy_from_user(&buf.rtdrv_rg_accessWanLimit_set_cfg, user, sizeof(rtdrv_rg_accessWanLimit_set_t));
			ret = rtk_rg_accessWanLimit_set(buf.rtdrv_rg_accessWanLimit_set_cfg.access_wan_info);
			break;

		case RTDRV_RG_ACCESSWANLIMITCATEGORY_SET:
			copy_from_user(&buf.rtdrv_rg_accessWanLimitCategory_set_cfg, user, sizeof(rtdrv_rg_accessWanLimitCategory_set_t));
			ret = rtk_rg_accessWanLimitCategory_set(buf.rtdrv_rg_accessWanLimitCategory_set_cfg.macCategory_info);
			break;

		case RTDRV_RG_SOFTWARESOURCEADDRLEARNINGLIMIT_SET:
			copy_from_user(&buf.rtdrv_rg_softwareSourceAddrLearningLimit_set_cfg, user, sizeof(rtdrv_rg_softwareSourceAddrLearningLimit_set_t));
			ret = rtk_rg_softwareSourceAddrLearningLimit_set(buf.rtdrv_rg_softwareSourceAddrLearningLimit_set_cfg.sa_learnLimit_info, buf.rtdrv_rg_softwareSourceAddrLearningLimit_set_cfg.port_idx);
			break;

		case RTDRV_RG_WLANSOFTWARESOURCEADDRLEARNINGLIMIT_SET:
			copy_from_user(&buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_set_cfg, user, sizeof(rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_set_t));
			ret = rtk_rg_wlanSoftwareSourceAddrLearningLimit_set(buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_set_cfg.sa_learnLimit_info, buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_set_cfg.wlan_idx, buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_set_cfg.dev_idx);
			break;

		case RTDRV_RG_DOSPORTMASKENABLE_SET:
			copy_from_user(&buf.rtdrv_rg_dosPortMaskEnable_set_cfg, user, sizeof(rtdrv_rg_dosPortMaskEnable_set_t));
			ret = rtk_rg_dosPortMaskEnable_set(buf.rtdrv_rg_dosPortMaskEnable_set_cfg.dos_port_mask);
			break;

		case RTDRV_RG_DOSTYPE_SET:
			copy_from_user(&buf.rtdrv_rg_dosType_set_cfg, user, sizeof(rtdrv_rg_dosType_set_t));
			//printk("RTDRV_RG_DOSTYPE_SET	RTDRV_RG_DOSTYPE_SET=0x%x \n",RTDRV_RG_DOSTYPE_SET);
			ret = rtk_rg_dosType_set(buf.rtdrv_rg_dosType_set_cfg.dos_type, buf.rtdrv_rg_dosType_set_cfg.dos_enabled, buf.rtdrv_rg_dosType_set_cfg.dos_action);
			break;

		case RTDRV_RG_DOSFLOODTYPE_SET:
			copy_from_user(&buf.rtdrv_rg_dosFloodType_set_cfg, user, sizeof(rtdrv_rg_dosFloodType_set_t));
			ret = rtk_rg_dosFloodType_set(buf.rtdrv_rg_dosFloodType_set_cfg.dos_type, buf.rtdrv_rg_dosFloodType_set_cfg.dos_enabled, buf.rtdrv_rg_dosFloodType_set_cfg.dos_action, buf.rtdrv_rg_dosFloodType_set_cfg.dos_threshold);
			break;

		case RTDRV_RG_PORTMIRROR_SET:
			copy_from_user(&buf.rtdrv_rg_portMirror_set_cfg, user, sizeof(rtdrv_rg_portMirror_set_t));
			ret = rtk_rg_portMirror_set(buf.rtdrv_rg_portMirror_set_cfg.portMirrorInfo);
			break;

		case RTDRV_RG_PORTMIRROR_CLEAR:
			//copy_from_user(&buf.rtdrv_rg_portMirror_clear_cfg, user, sizeof(rtdrv_rg_portMirror_clear_t));
			ret = rtk_rg_portMirror_clear();
			break;
		case RTDRV_RG_PORTEGRBANDWIDTHCTRLRATE_SET:
			copy_from_user(&buf.rtdrv_rg_portEgrBandwidthCtrlRate_set_cfg, user, sizeof(rtdrv_rg_portEgrBandwidthCtrlRate_set_t));
			ret = rtk_rg_portEgrBandwidthCtrlRate_set(buf.rtdrv_rg_portEgrBandwidthCtrlRate_set_cfg.port, buf.rtdrv_rg_portEgrBandwidthCtrlRate_set_cfg.rate);
			break;

		case RTDRV_RG_PORTIGRBANDWIDTHCTRLRATE_SET:
			copy_from_user(&buf.rtdrv_rg_portIgrBandwidthCtrlRate_set_cfg, user, sizeof(rtdrv_rg_portIgrBandwidthCtrlRate_set_t));
			ret = rtk_rg_portIgrBandwidthCtrlRate_set(buf.rtdrv_rg_portIgrBandwidthCtrlRate_set_cfg.port, buf.rtdrv_rg_portIgrBandwidthCtrlRate_set_cfg.rate);
			break;

		case RTDRV_RG_PHYPORTFORCEABILITY_SET:
			copy_from_user(&buf.rtdrv_rg_phyPortForceAbility_set_cfg, user, sizeof(rtdrv_rg_phyPortForceAbility_set_t));
			ret = rtk_rg_phyPortForceAbility_set(buf.rtdrv_rg_phyPortForceAbility_set_cfg.port, buf.rtdrv_rg_phyPortForceAbility_set_cfg.ability);
			break;

		case RTDRV_RG_CPUPORTFORCETRAFFICCTRL_SET:
			copy_from_user(&buf.rtdrv_rg_cpuPortForceTrafficCtrl_set_cfg, user, sizeof(rtdrv_rg_cpuPortForceTrafficCtrl_set_t));
			ret = rtk_rg_cpuPortForceTrafficCtrl_set(buf.rtdrv_rg_cpuPortForceTrafficCtrl_set_cfg.tx_fc_state, buf.rtdrv_rg_cpuPortForceTrafficCtrl_set_cfg.rx_fc_state);
			break;

		case RTDRV_RG_PORTMIBINFO_CLEAR:
			copy_from_user(&buf.rtdrv_rg_portMibInfo_clear_cfg, user, sizeof(rtdrv_rg_portMibInfo_clear_t));
			ret = rtk_rg_portMibInfo_clear(buf.rtdrv_rg_portMibInfo_clear_cfg.port);
			break;

		case RTDRV_RG_PORTISOLATION_SET:
			copy_from_user(&buf.rtdrv_rg_portIsolation_set_cfg, user, sizeof(rtdrv_rg_portIsolation_set_t));
			ret = rtk_rg_portIsolation_set(buf.rtdrv_rg_portIsolation_set_cfg.isolationSetting);
			break;

		case RTDRV_RG_STORMCONTROL_DEL:
			copy_from_user(&buf.rtdrv_rg_stormControl_del_cfg, user, sizeof(rtdrv_rg_stormControl_del_t));
			ret = rtk_rg_stormControl_del(buf.rtdrv_rg_stormControl_del_cfg.stormInfo_idx);
			break;

		case RTDRV_RG_SHAREMETER_SET:
			copy_from_user(&buf.rtdrv_rg_shareMeter_set_cfg, user, sizeof(rtdrv_rg_shareMeter_set_t));
			ret = rtk_rg_shareMeter_set(buf.rtdrv_rg_shareMeter_set_cfg.index, buf.rtdrv_rg_shareMeter_set_cfg.rate, buf.rtdrv_rg_shareMeter_set_cfg.ifgInclude);
			break;

		case RTDRV_RG_QOSSTRICTPRIORITYORWEIGHTFAIRQUEUE_SET:
			copy_from_user(&buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_set_cfg, user, sizeof(rtdrv_rg_qosStrictPriorityOrWeightFairQueue_set_t));
			ret = rtk_rg_qosStrictPriorityOrWeightFairQueue_set(buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_set_cfg.port_idx, buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_set_cfg.q_weight);
			break;

		case RTDRV_RG_QOSINTERNALPRIMAPTOQUEUEID_SET:
			copy_from_user(&buf.rtdrv_rg_qosInternalPriMapToQueueId_set_cfg, user, sizeof(rtdrv_rg_qosInternalPriMapToQueueId_set_t));
			ret = rtk_rg_qosInternalPriMapToQueueId_set(buf.rtdrv_rg_qosInternalPriMapToQueueId_set_cfg.intPri,buf.rtdrv_rg_qosInternalPriMapToQueueId_set_cfg.queueId);
			break;

		case RTDRV_RG_QOSINTERNALPRIDECISIONBYWEIGHT_SET:
			copy_from_user(&buf.rtdrv_rg_qosInternalPriDecisionByWeight_set_cfg, user, sizeof(rtdrv_rg_qosInternalPriDecisionByWeight_set_t));
			ret = rtk_rg_qosInternalPriDecisionByWeight_set(buf.rtdrv_rg_qosInternalPriDecisionByWeight_set_cfg.weightOfPriSel);
			break;

		case RTDRV_RG_QOSDSCPREMAPTOINTERNALPRI_SET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemapToInternalPri_set_cfg, user, sizeof(rtdrv_rg_qosDscpRemapToInternalPri_set_t));
			ret = rtk_rg_qosDscpRemapToInternalPri_set(buf.rtdrv_rg_qosDscpRemapToInternalPri_set_cfg.dscp, buf.rtdrv_rg_qosDscpRemapToInternalPri_set_cfg.intPri);
			break;

		case RTDRV_RG_QOSDOT1PPRIREMAPTOINTERNALPRI_SET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_set_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemapToInternalPri_set_t));
			ret = rtk_rg_qosDot1pPriRemapToInternalPri_set(buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_set_cfg.dot1p, buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_set_cfg.intPri);
			break;

		case RTDRV_RG_QOSPORTBASEDPRIORITY_SET:
			copy_from_user(&buf.rtdrv_rg_qosPortBasedPriority_set_cfg, user, sizeof(rtdrv_rg_qosPortBasedPriority_set_t));
			ret = rtk_rg_qosPortBasedPriority_set(buf.rtdrv_rg_qosPortBasedPriority_set_cfg.port, buf.rtdrv_rg_qosPortBasedPriority_set_cfg.intPri);
			break;

		case RTDRV_RG_QOSDSCPREMARKEGRESSPORTENABLEANDSRCSELECT_SET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_t));
			ret = rtk_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set(buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_cfg.port, buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_cfg.is_enabled, buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_cfg.src_sel);
			break;

		case RTDRV_RG_QOSDSCPREMARKBYINTERNALPRI_SET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkByInternalPri_set_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkByInternalPri_set_t));
			ret = rtk_rg_qosDscpRemarkByInternalPri_set(buf.rtdrv_rg_qosDscpRemarkByInternalPri_set_cfg.int_pri, buf.rtdrv_rg_qosDscpRemarkByInternalPri_set_cfg.rmk_dscp);
			break;

		case RTDRV_RG_QOSDSCPREMARKBYDSCP_SET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkByDscp_set_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkByDscp_set_t));
			ret = rtk_rg_qosDscpRemarkByDscp_set(buf.rtdrv_rg_qosDscpRemarkByDscp_set_cfg.dscp, buf.rtdrv_rg_qosDscpRemarkByDscp_set_cfg.rmk_dscp);
			break;

		case RTDRV_RG_QOSDOT1PPRIREMARKBYINTERNALPRIEGRESSPORTENABLE_SET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_set_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_set_t));
			ret = rtk_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_set(buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_set_cfg.port,buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_set_cfg.enable);
			break;

		case RTDRV_RG_QOSDOT1PPRIREMARKBYINTERNALPRI_SET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_set_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPri_set_t));
			ret = rtk_rg_qosDot1pPriRemarkByInternalPri_set(buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_set_cfg.int_pri, buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_set_cfg.rmk_dot1p);
			break;

		case RTDRV_RG_PORTBASEDCVLANID_SET:
			copy_from_user(&buf.rtdrv_rg_portBasedCVlanId_set_cfg, user, sizeof(rtdrv_rg_portBasedCVlanId_set_t));
			ret = rtk_rg_portBasedCVlanId_set(buf.rtdrv_rg_portBasedCVlanId_set_cfg.port_idx, buf.rtdrv_rg_portBasedCVlanId_set_cfg.pvid);
			break;

		case RTDRV_RG_WLANDEVBASEDCVLANID_SET:
			copy_from_user(&buf.rtdrv_rg_wlanDevBasedCVlanId_set_cfg, user, sizeof(rtdrv_rg_wlanDevBasedCVlanId_set_t));
			ret = rtk_rg_wlanDevBasedCVlanId_set(buf.rtdrv_rg_wlanDevBasedCVlanId_set_cfg.wlan_idx, buf.rtdrv_rg_wlanDevBasedCVlanId_set_cfg.dev_idx, buf.rtdrv_rg_wlanDevBasedCVlanId_set_cfg.dvid);
			break;

		case RTDRV_RG_CLASSIFYENTRY_DEL:
			copy_from_user(&buf.rtdrv_rg_classifyEntry_del_cfg, user, sizeof(rtdrv_rg_classifyEntry_del_t));
			ret = rtk_rg_classifyEntry_del(buf.rtdrv_rg_classifyEntry_del_cfg.index);
			break;

		case RTDRV_RG_GATEWAYSERVICEPORTREGISTER_DEL:
			copy_from_user(&buf.rtdrv_rg_gatewayServicePortRegister_del_cfg, user, sizeof(rtdrv_rg_gatewayServicePortRegister_del_t));
			ret = rtk_rg_gatewayServicePortRegister_del(buf.rtdrv_rg_gatewayServicePortRegister_del_cfg.index);
			break;

		case RTDRV_RG_GPONDSBCFILTERANDREMARKING_ENABLE:
			copy_from_user(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_Enable_cfg, user, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_Enable_t));
			ret = rtk_rg_gponDsBcFilterAndRemarking_Enable(buf.rtdrv_rg_gponDsBcFilterAndRemarking_Enable_cfg.enable);
			break;

		case RTDRV_RG_GPONDSBCFILTERANDREMARKING_DEL:
			copy_from_user(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_del_cfg, user, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_del_t));
			ret = rtk_rg_gponDsBcFilterAndRemarking_del(buf.rtdrv_rg_gponDsBcFilterAndRemarking_del_cfg.index);
			break;

		case RTDRV_RG_GPONDSBCFILTERANDREMARKING_DEL_ALL:
			copy_from_user(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_del_all_cfg, user, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_del_all_t));
			ret = rtk_rg_gponDsBcFilterAndRemarking_del_all();
			break;

		case RTDRV_RG_STPBLOCKINGPORTMASK_SET:
			copy_from_user(&buf.rtdrv_rg_stpBlockingPortmask_set_cfg, user, sizeof(rtdrv_rg_stpBlockingPortmask_set_t));
			ret = rtk_rg_stpBlockingPortmask_set(buf.rtdrv_rg_stpBlockingPortmask_set_cfg.Mask);
			break;

		case RTDRV_RG_DSLITECONTROL_SET:
			copy_from_user(&buf.rtdrv_rg_dsliteControl_set_cfg, user, sizeof(rtdrv_rg_dsliteControl_set_t));
			ret = rtk_rg_dsliteControl_set(buf.rtdrv_rg_dsliteControl_set_cfg.ctrlType, buf.rtdrv_rg_dsliteControl_set_cfg.act);
			break;

		case RTDRV_RG_INTERFACEMIBCOUNTER_DEL:
			copy_from_user(&buf.rtdrv_rg_interfaceMibCounter_del_cfg, user, sizeof(rtdrv_rg_interfaceMibCounter_del_t));
			ret = rtk_rg_interfaceMibCounter_del(buf.rtdrv_rg_interfaceMibCounter_del_cfg.intf_idx);
			break;

		case RTDRV_RG_SVLANTPID2_ENABLE_SET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid2_enable_set_cfg, user, sizeof(rtdrv_rg_svlanTpid2_enable_set_t));
			ret = rtk_rg_svlanTpid2_enable_set(buf.rtdrv_rg_svlanTpid2_enable_set_cfg.enable);
			break;
		
		case RTDRV_RG_SVLANTPID2_SET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid2_set_cfg, user, sizeof(rtdrv_rg_svlanTpid2_set_t));
			ret = rtk_rg_svlanTpid2_set(buf.rtdrv_rg_svlanTpid2_set_cfg.svlan_tag_id);
			break;		
		case RTDRV_RG_HOSTPOLICELOGGING_DEL:
			copy_from_user(&buf.rtdrv_rg_hostPoliceLogging_del_cfg, user, sizeof(rtdrv_rg_hostPoliceLogging_del_t));
			ret = rtk_rg_hostPoliceLogging_del(buf.rtdrv_rg_hostPoliceLogging_del_cfg.host_idx);
			break;
			
		case RTDRV_RG_STATICROUTE_DEL:
			copy_from_user(&buf.rtdrv_rg_staticRoute_del_cfg, user, sizeof(rtdrv_rg_staticRoute_del_t));
			ret = rtk_rg_staticRoute_del(buf.rtdrv_rg_staticRoute_del_cfg.index);
			break;
#endif
    }

	return ret;
}


/* Function Name:
 *      do_rtdrv_rg_get_ctl
 * Description:
 *      This function is called whenever a process tries to do getsockopt
 * Input:
 *      *sk   - network layer representation of sockets
 *      cmd   - ioctl commands
 * Output:
 *      *user - data buffer handled between user and kernel space
 *      len   - data length
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      None
 */
int32 do_rtdrv_rg_get_ctl(struct sock *sk, int cmd, void *user, int *len)
{
    int32               ret = RT_ERR_FAILED;
    rtdrv_rg_union_t    buf;
    switch(cmd)
    {
#if defined(CONFIG_RTK_L34_ENABLE) && CONFIG_RTK_L34_ENABLE==1 || defined(CONFIG_XDSL_RG_DIAGSHELL)
		/* RG GET API */
		case RTDRV_RG_DRIVERVERSION_GET:
			copy_from_user(&buf.rtdrv_rg_driverVersion_get_cfg, user, sizeof(rtdrv_rg_driverVersion_get_t));
			ret = rtk_rg_driverVersion_get(&buf.rtdrv_rg_driverVersion_get_cfg.version_string);
			copy_to_user(user, &buf.rtdrv_rg_driverVersion_get_cfg, sizeof(rtdrv_rg_driverVersion_get_t));
			break;


		case RTDRV_RG_INITPARAM_GET:
			copy_from_user(&buf.rtdrv_rg_initParam_get_cfg, user, sizeof(rtdrv_rg_initParam_get_t));
			ret = rtk_rg_initParam_get(&buf.rtdrv_rg_initParam_get_cfg.init_param);
			copy_to_user(user, &buf.rtdrv_rg_initParam_get_cfg, sizeof(rtdrv_rg_initParam_get_t));
			break;

		case RTDRV_RG_INITPARAM_SET:
			copy_from_user(&buf.rtdrv_rg_initParam_set_cfg, user, sizeof(rtdrv_rg_initParam_set_t));
			if(_rg_init_parameterCheck(&buf.rtdrv_rg_initParam_set_cfg.init_param)){

#if defined(CONFIG_RG_CALLBACK) && CONFIG_RG_CALLBACK==1
				if((int)buf.rtdrv_rg_initParam_set_cfg.init_param.initByHwCallBack == 0xfffffffe){
					//special case for regist default callback function
					buf.rtdrv_rg_initParam_set_cfg.init_param.initByHwCallBack = _rtk_rg_initParameterSetByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.arpAddByHwCallBack = _rtk_rg_arpAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.arpDelByHwCallBack = _rtk_rg_arpDelByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.macAddByHwCallBack = _rtk_rg_macAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.macDelByHwCallBack = _rtk_rg_macDelByHwCallBack;
//5
					buf.rtdrv_rg_initParam_set_cfg.init_param.routingAddByHwCallBack = _rtk_rg_routingAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.routingDelByHwCallBack = _rtk_rg_routingDelByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.naptAddByHwCallBack = _rtk_rg_naptAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.naptDelByHwCallBack = _rtk_rg_naptDelByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.bindingAddByHwCallBack = _rtk_rg_bindingAddByHwCallBack;
//10
					buf.rtdrv_rg_initParam_set_cfg.init_param.bindingDelByHwCallBack = _rtk_rg_bindingDelByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.interfaceAddByHwCallBack = _rtk_rg_interfaceAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.interfaceDelByHwCallBack = _rtk_rg_interfaceDelByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.neighborAddByHwCallBack = _rtk_rg_neighborAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.neighborDelByHwCallBack = _rtk_rg_neighborDelByHwCallBack;
//15
					buf.rtdrv_rg_initParam_set_cfg.init_param.v6RoutingAddByHwCallBack = _rtk_rg_v6RoutingAddByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.v6RoutingDelByHwCallBack = _rtk_rg_v6RoutingDelByHwCallBack;
					//buf.rtdrv_rg_initParam_set_cfg.init_param.naptInboundConnLookupFirstCallBack registered at _rtk_rg_initParam_set if needed
					//buf.rtdrv_rg_initParam_set_cfg.init_param.naptInboundConnLookupSecondCallBack registered at _rtk_rg_initParam_set if needed
					//buf.rtdrv_rg_initParam_set_cfg.init_param.naptInboundConnLookupThirdCallBack registered at _rtk_rg_initParam_set if needed
//20
					buf.rtdrv_rg_initParam_set_cfg.init_param.dhcpRequestByHwCallBack = _rtk_rg_dhcpRequestByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.pppoeBeforeDiagByHwCallBack = _rtk_rg_pppoeBeforeDiagByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.pptpBeforeDialByHwCallBack = _rtk_rg_pptpBeforeDialByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.l2tpBeforeDialByHwCallBack = _rtk_rg_l2tpBeforeDialByHwCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.pppoeDsliteBeforeDialByHwCallBack = _rtk_rg_pppoeDsliteBeforeDialByHwCallBack;
//25
					//buf.rtdrv_rg_initParam_set_cfg.init_param.ipv6NaptInboundConnLookupFirstCallBack registered at _rtk_rg_initParam_set if needed
					//buf.rtdrv_rg_initParam_set_cfg.init_param.ipv6NaptInboundConnLookupSecondCallBack registered at _rtk_rg_initParam_set if needed
					//buf.rtdrv_rg_initParam_set_cfg.init_param.ipv6NaptInboundConnLookupThirdCallBack registered at _rtk_rg_initParam_set if needed
					buf.rtdrv_rg_initParam_set_cfg.init_param.softwareNaptInfoAddCallBack = _rtk_rg_softwareNaptInfoAddCallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.softwareNaptInfoDeleteCallBack = _rtk_rg_softwareNaptInfoDeleteCallBack;
//30
					buf.rtdrv_rg_initParam_set_cfg.init_param.naptPreRouteDPICallBack = _rtk_rg_naptPreRouteDPICallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.naptForwardDPICallBack = _rtk_rg_naptForwardDPICallBack;
					buf.rtdrv_rg_initParam_set_cfg.init_param.pppoeLCPStateCallBack = _rtk_rg_pppoeLCPStateCallBack;
				}
#endif


				ret = rtk_rg_initParam_set(&buf.rtdrv_rg_initParam_set_cfg.init_param);
				copy_to_user(user, &buf.rtdrv_rg_initParam_set_cfg, sizeof(rtdrv_rg_initParam_set_t));
			}else{
				ret = rtk_rg_initParam_set(NULL);
			}
			break;

		case RTDRV_RG_LANINTERFACE_ADD:
			copy_from_user(&buf.rtdrv_rg_lanInterface_add_cfg, user, sizeof(rtdrv_rg_lanInterface_add_t));
			ret = rtk_rg_lanInterface_add(&buf.rtdrv_rg_lanInterface_add_cfg.lan_info, &buf.rtdrv_rg_lanInterface_add_cfg.intf_idx);
			if(ret!=RT_ERR_OK) printk("rtk_rg_lanInterface_add failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_lanInterface_add_cfg, sizeof(rtdrv_rg_lanInterface_add_t));
			break;

		case RTDRV_RG_WANINTERFACE_ADD:
			copy_from_user(&buf.rtdrv_rg_wanInterface_add_cfg, user, sizeof(rtdrv_rg_wanInterface_add_t));
			ret = rtk_rg_wanInterface_add(&buf.rtdrv_rg_wanInterface_add_cfg.wanintf, &buf.rtdrv_rg_wanInterface_add_cfg.wan_intf_idx);
			if(ret!=RT_ERR_OK) printk("rtk_rg_wanInterface_add failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_wanInterface_add_cfg, sizeof(rtdrv_rg_wanInterface_add_t));
			break;

		case RTDRV_RG_STATICINFO_SET:
			copy_from_user(&buf.rtdrv_rg_staticInfo_set_cfg, user, sizeof(rtdrv_rg_staticInfo_set_t));
			ret = rtk_rg_staticInfo_set(buf.rtdrv_rg_staticInfo_set_cfg.wan_intf_idx, &buf.rtdrv_rg_staticInfo_set_cfg.static_info);
			if(ret!=RT_ERR_OK) printk("rtk_rg_staticInfo_set failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_staticInfo_set_cfg, sizeof(rtdrv_rg_staticInfo_set_t));
			break;

		case RTDRV_RG_DSLITEINFO_SET:
			copy_from_user(&buf.rtdrv_rg_dsliteInfo_set_cfg, user, sizeof(rtdrv_rg_dsliteInfo_set_t));
			ret = rtk_rg_dsliteInfo_set(buf.rtdrv_rg_dsliteInfo_set_cfg.wan_intf_idx, &buf.rtdrv_rg_dsliteInfo_set_cfg.dslite_info);
			copy_to_user(user, &buf.rtdrv_rg_dsliteInfo_set_cfg, sizeof(rtdrv_rg_dsliteInfo_set_t));
			break;

		case RTDRV_RG_DHCPCLIENTINFO_SET:
			copy_from_user(&buf.rtdrv_rg_dhcpClientInfo_set_cfg, user, sizeof(rtdrv_rg_dhcpClientInfo_set_t));
			ret = rtk_rg_dhcpClientInfo_set(buf.rtdrv_rg_dhcpClientInfo_set_cfg.wan_intf_idx, &buf.rtdrv_rg_dhcpClientInfo_set_cfg.dhcpClient_info);
			if(ret!=RT_ERR_OK) printk("rtk_rg_dhcpClientInfo_set failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_dhcpClientInfo_set_cfg, sizeof(rtdrv_rg_dhcpClientInfo_set_t));
			break;

		case RTDRV_RG_PPPOECLIENTINFOBEFOREDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pppoeClientInfoBeforeDial_set_cfg, user, sizeof(rtdrv_rg_pppoeClientInfoBeforeDial_set_t));
			ret = rtk_rg_pppoeClientInfoBeforeDial_set(buf.rtdrv_rg_pppoeClientInfoBeforeDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pppoeClientInfoBeforeDial_set_cfg.app_info);
			if(ret!=RT_ERR_OK) printk("rtk_rg_pppoeClientInfoBeforeDial_set failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_pppoeClientInfoBeforeDial_set_cfg, sizeof(rtdrv_rg_pppoeClientInfoBeforeDial_set_t));
			break;

		case RTDRV_RG_PPPOECLIENTINFOAFTERDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pppoeClientInfoAfterDial_set_cfg, user, sizeof(rtdrv_rg_pppoeClientInfoAfterDial_set_t));
			ret = rtk_rg_pppoeClientInfoAfterDial_set(buf.rtdrv_rg_pppoeClientInfoAfterDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pppoeClientInfoAfterDial_set_cfg.clientPppoe_info);
			if(ret!=RT_ERR_OK) printk("rtk_rg_pppoeClientInfoAfterDial_set failed: ret=0x%x\n",ret);
			copy_to_user(user, &buf.rtdrv_rg_pppoeClientInfoAfterDial_set_cfg, sizeof(rtdrv_rg_pppoeClientInfoAfterDial_set_t));
			break;

		case RTDRV_RG_PPTPCLIENTINFOBEFOREDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pptpClientInfoBeforeDial_set_cfg, user, sizeof(rtdrv_rg_pptpClientInfoBeforeDial_set_t));
			ret = rtk_rg_pptpClientInfoBeforeDial_set(buf.rtdrv_rg_pptpClientInfoBeforeDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pptpClientInfoBeforeDial_set_cfg.app_info);
			copy_to_user(user, &buf.rtdrv_rg_pptpClientInfoBeforeDial_set_cfg, sizeof(rtdrv_rg_pptpClientInfoBeforeDial_set_t));
			break;

		case RTDRV_RG_PPTPCLIENTINFOAFTERDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pptpClientInfoAfterDial_set_cfg, user, sizeof(rtdrv_rg_pptpClientInfoAfterDial_set_t));
			ret = rtk_rg_pptpClientInfoAfterDial_set(buf.rtdrv_rg_pptpClientInfoAfterDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pptpClientInfoAfterDial_set_cfg.clientPptp_info);
			copy_to_user(user, &buf.rtdrv_rg_pptpClientInfoAfterDial_set_cfg, sizeof(rtdrv_rg_pptpClientInfoAfterDial_set_t));
			break;

		case RTDRV_RG_L2TPCLIENTINFOBEFOREDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_l2tpClientInfoBeforeDial_set_cfg, user, sizeof(rtdrv_rg_l2tpClientInfoBeforeDial_set_t));
			ret = rtk_rg_l2tpClientInfoBeforeDial_set(buf.rtdrv_rg_l2tpClientInfoBeforeDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_l2tpClientInfoBeforeDial_set_cfg.app_info);
			copy_to_user(user, &buf.rtdrv_rg_l2tpClientInfoBeforeDial_set_cfg, sizeof(rtdrv_rg_l2tpClientInfoBeforeDial_set_t));
			break;

		case RTDRV_RG_L2TPCLIENTINFOAFTERDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_l2tpClientInfoAfterDial_set_cfg, user, sizeof(rtdrv_rg_l2tpClientInfoAfterDial_set_t));
			ret = rtk_rg_l2tpClientInfoAfterDial_set(buf.rtdrv_rg_l2tpClientInfoAfterDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_l2tpClientInfoAfterDial_set_cfg.clientL2tp_info);
			copy_to_user(user, &buf.rtdrv_rg_l2tpClientInfoAfterDial_set_cfg, sizeof(rtdrv_rg_l2tpClientInfoAfterDial_set_t));
			break;

		case RTDRV_RG_PPPOEDSLITEINFOBEFOREDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pppoeDsliteInfoBeforeDial_set_cfg, user, sizeof(rtdrv_rg_pppoeDsliteInfoBeforeDial_set_t));
			ret = rtk_rg_pppoeDsliteInfoBeforeDial_set(buf.rtdrv_rg_pppoeDsliteInfoBeforeDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pppoeDsliteInfoBeforeDial_set_cfg.app_info);
			copy_to_user(user, &buf.rtdrv_rg_pppoeDsliteInfoBeforeDial_set_cfg, sizeof(rtdrv_rg_pppoeDsliteInfoBeforeDial_set_t));
			break;

		case RTDRV_RG_PPPOEDSLITEINFOAFTERDIAL_SET:
			copy_from_user(&buf.rtdrv_rg_pppoeDsliteInfoAfterDial_set_cfg, user, sizeof(rtdrv_rg_pppoeDsliteInfoAfterDial_set_t));
			ret = rtk_rg_pppoeDsliteInfoAfterDial_set(buf.rtdrv_rg_pppoeDsliteInfoAfterDial_set_cfg.wan_intf_idx, &buf.rtdrv_rg_pppoeDsliteInfoAfterDial_set_cfg.pppoeDslite_info);
			copy_to_user(user, &buf.rtdrv_rg_pppoeDsliteInfoAfterDial_set_cfg, sizeof(rtdrv_rg_pppoeDsliteInfoAfterDial_set_t));
			break;

		case RTDRV_RG_INTFINFO_FIND:
			copy_from_user(&buf.rtdrv_rg_intfInfo_find_cfg, user, sizeof(rtdrv_rg_intfInfo_find_t));
			ret = rtk_rg_intfInfo_find(&buf.rtdrv_rg_intfInfo_find_cfg.intf_info, &buf.rtdrv_rg_intfInfo_find_cfg.valid_lan_or_wan_intf_idx);
			copy_to_user(user, &buf.rtdrv_rg_intfInfo_find_cfg, sizeof(rtdrv_rg_intfInfo_find_t));
			break;

		case RTDRV_RG_SVLANTPID_GET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid_get_cfg, user, sizeof(rtdrv_rg_svlanTpid_get_t));
			ret = rtk_rg_svlanTpid_get(&buf.rtdrv_rg_svlanTpid_get_cfg.pSvlanTagId);
			copy_to_user(user, &buf.rtdrv_rg_svlanTpid_get_cfg, sizeof(rtdrv_rg_svlanTpid_get_t));
			break;

		case RTDRV_RG_SVLANSERVICEPORT_GET:
			copy_from_user(&buf.rtdrv_rg_svlanServicePort_get_cfg, user, sizeof(rtdrv_rg_svlanServicePort_get_t));
			ret = rtk_rg_svlanServicePort_get(buf.rtdrv_rg_svlanServicePort_get_cfg.port, &buf.rtdrv_rg_svlanServicePort_get_cfg.pEnable);
			copy_to_user(user, &buf.rtdrv_rg_svlanServicePort_get_cfg, sizeof(rtdrv_rg_svlanServicePort_get_t));
			break;

		case RTDRV_RG_CVLAN_ADD:
			copy_from_user(&buf.rtdrv_rg_cvlan_add_cfg, user, sizeof(rtdrv_rg_cvlan_add_t));
			ret = rtk_rg_cvlan_add(&buf.rtdrv_rg_cvlan_add_cfg.cvlan_info);
			copy_to_user(user, &buf.rtdrv_rg_cvlan_add_cfg, sizeof(rtdrv_rg_cvlan_add_t));
			break;

		case RTDRV_RG_CVLAN_GET:
			copy_from_user(&buf.rtdrv_rg_cvlan_get_cfg, user, sizeof(rtdrv_rg_cvlan_get_t));
			ret = rtk_rg_cvlan_get(&buf.rtdrv_rg_cvlan_get_cfg.cvlan_info);
			copy_to_user(user, &buf.rtdrv_rg_cvlan_get_cfg, sizeof(rtdrv_rg_cvlan_get_t));
			break;

		case RTDRV_RG_VLANBINDING_ADD:
			copy_from_user(&buf.rtdrv_rg_vlanBinding_add_cfg, user, sizeof(rtdrv_rg_vlanBinding_add_t));
			ret = rtk_rg_vlanBinding_add(&buf.rtdrv_rg_vlanBinding_add_cfg.vlan_binding_info, &buf.rtdrv_rg_vlanBinding_add_cfg.vlan_binding_idx);
			copy_to_user(user, &buf.rtdrv_rg_vlanBinding_add_cfg, sizeof(rtdrv_rg_vlanBinding_add_t));
			break;

		case RTDRV_RG_VLANBINDING_FIND:
			copy_from_user(&buf.rtdrv_rg_vlanBinding_find_cfg, user, sizeof(rtdrv_rg_vlanBinding_find_t));
			ret = rtk_rg_vlanBinding_find(&buf.rtdrv_rg_vlanBinding_find_cfg.vlan_binding_info, &buf.rtdrv_rg_vlanBinding_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_vlanBinding_find_cfg, sizeof(rtdrv_rg_vlanBinding_find_t));
			break;


		case RTDRV_RG_ALGSERVERINLANAPPSIPADDR_ADD:
			copy_from_user(&buf.rtdrv_rg_algServerInLanAppsIpAddr_add_cfg, user, sizeof(rtdrv_rg_algServerInLanAppsIpAddr_add_t));
			ret = rtk_rg_algServerInLanAppsIpAddr_add(&buf.rtdrv_rg_algServerInLanAppsIpAddr_add_cfg.srvIpMapping);
			copy_to_user(user, &buf.rtdrv_rg_algServerInLanAppsIpAddr_add_cfg, sizeof(rtdrv_rg_algServerInLanAppsIpAddr_add_t));
			break;

		case RTDRV_RG_ALGAPPS_GET:
			copy_from_user(&buf.rtdrv_rg_algApps_get_cfg, user, sizeof(rtdrv_rg_algApps_get_t));
			ret = rtk_rg_algApps_get(&buf.rtdrv_rg_algApps_get_cfg.alg_app);
			copy_to_user(user, &buf.rtdrv_rg_algApps_get_cfg, sizeof(rtdrv_rg_algApps_get_t));
			break;

		case RTDRV_RG_DMZHOST_SET:
			copy_from_user(&buf.rtdrv_rg_dmzHost_set_cfg, user, sizeof(rtdrv_rg_dmzHost_set_t));
			ret = rtk_rg_dmzHost_set(buf.rtdrv_rg_dmzHost_set_cfg.wan_intf_idx, &buf.rtdrv_rg_dmzHost_set_cfg.dmz_info);
			copy_to_user(user, &buf.rtdrv_rg_dmzHost_set_cfg, sizeof(rtdrv_rg_dmzHost_set_t));
			break;

		case RTDRV_RG_DMZHOST_GET:
			copy_from_user(&buf.rtdrv_rg_dmzHost_get_cfg, user, sizeof(rtdrv_rg_dmzHost_get_t));
			ret = rtk_rg_dmzHost_get(buf.rtdrv_rg_dmzHost_get_cfg.wan_intf_idx, &buf.rtdrv_rg_dmzHost_get_cfg.dmz_info);
			copy_to_user(user, &buf.rtdrv_rg_dmzHost_get_cfg, sizeof(rtdrv_rg_dmzHost_get_t));
			break;

		case RTDRV_RG_VIRTUALSERVER_ADD:
			copy_from_user(&buf.rtdrv_rg_virtualServer_add_cfg, user, sizeof(rtdrv_rg_virtualServer_add_t));
			ret = rtk_rg_virtualServer_add(&buf.rtdrv_rg_virtualServer_add_cfg.virtual_server, &buf.rtdrv_rg_virtualServer_add_cfg.virtual_server_idx);
			copy_to_user(user, &buf.rtdrv_rg_virtualServer_add_cfg, sizeof(rtdrv_rg_virtualServer_add_t));
			break;

		case RTDRV_RG_VIRTUALSERVER_FIND:
			copy_from_user(&buf.rtdrv_rg_virtualServer_find_cfg, user, sizeof(rtdrv_rg_virtualServer_find_t));
			ret = rtk_rg_virtualServer_find(&buf.rtdrv_rg_virtualServer_find_cfg.virtual_server, &buf.rtdrv_rg_virtualServer_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_virtualServer_find_cfg, sizeof(rtdrv_rg_virtualServer_find_t));
			break;

		case RTDRV_RG_ACLFILTERANDQOS_ADD:
			copy_from_user(&buf.rtdrv_rg_aclFilterAndQos_add_cfg, user, sizeof(rtdrv_rg_aclFilterAndQos_add_t));
			ret = rtk_rg_aclFilterAndQos_add(&buf.rtdrv_rg_aclFilterAndQos_add_cfg.acl_filter, &buf.rtdrv_rg_aclFilterAndQos_add_cfg.acl_filter_idx);
			copy_to_user(user, &buf.rtdrv_rg_aclFilterAndQos_add_cfg, sizeof(rtdrv_rg_aclFilterAndQos_add_t));
			break;

		case RTDRV_RG_ACLFILTERANDQOS_FIND:
			copy_from_user(&buf.rtdrv_rg_aclFilterAndQos_find_cfg, user, sizeof(rtdrv_rg_aclFilterAndQos_find_t));
			ret = rtk_rg_aclFilterAndQos_find(&buf.rtdrv_rg_aclFilterAndQos_find_cfg.acl_filter, &buf.rtdrv_rg_aclFilterAndQos_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_aclFilterAndQos_find_cfg, sizeof(rtdrv_rg_aclFilterAndQos_find_t));
			break;

		case RTDRV_RG_NAPTFILTERANDQOS_ADD:
			copy_from_user(&buf.rtdrv_rg_naptFilterAndQos_add_cfg, user, sizeof(rtdrv_rg_naptFilterAndQos_add_t));
			ret = rtk_rg_naptFilterAndQos_add(&buf.rtdrv_rg_naptFilterAndQos_add_cfg.index, &buf.rtdrv_rg_naptFilterAndQos_add_cfg.napt_filter);
			copy_to_user(user, &buf.rtdrv_rg_naptFilterAndQos_add_cfg, sizeof(rtdrv_rg_naptFilterAndQos_add_t));
			break;

		case RTDRV_RG_NAPTFILTERANDQOS_FIND:
			copy_from_user(&buf.rtdrv_rg_naptFilterAndQos_find_cfg, user, sizeof(rtdrv_rg_naptFilterAndQos_find_t));
			ret = rtk_rg_naptFilterAndQos_find(&buf.rtdrv_rg_naptFilterAndQos_find_cfg.index, &buf.rtdrv_rg_naptFilterAndQos_find_cfg.napt_filter);
			copy_to_user(user, &buf.rtdrv_rg_naptFilterAndQos_find_cfg, sizeof(rtdrv_rg_naptFilterAndQos_find_t));
			break;

		case RTDRV_RG_MACFILTER_ADD:
			copy_from_user(&buf.rtdrv_rg_macFilter_add_cfg, user, sizeof(rtdrv_rg_macFilter_add_t));
			ret = rtk_rg_macFilter_add(&buf.rtdrv_rg_macFilter_add_cfg.macFilterEntry, &buf.rtdrv_rg_macFilter_add_cfg.mac_filter_idx);
			copy_to_user(user, &buf.rtdrv_rg_macFilter_add_cfg, sizeof(rtdrv_rg_macFilter_add_t));
			break;

		case RTDRV_RG_MACFILTER_FIND:
			copy_from_user(&buf.rtdrv_rg_macFilter_find_cfg, user, sizeof(rtdrv_rg_macFilter_find_t));
			ret = rtk_rg_macFilter_find(&buf.rtdrv_rg_macFilter_find_cfg.macFilterEntry, &buf.rtdrv_rg_macFilter_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_macFilter_find_cfg, sizeof(rtdrv_rg_macFilter_find_t));
			break;


		case RTDRV_RG_URLFILTERSTRING_ADD:
			copy_from_user(&buf.rtdrv_rg_urlFilterString_add_cfg, user, sizeof(rtdrv_rg_urlFilterString_add_t));
			ret = rtk_rg_urlFilterString_add(&buf.rtdrv_rg_urlFilterString_add_cfg.filter, &buf.rtdrv_rg_urlFilterString_add_cfg.url_idx);
			copy_to_user(user, &buf.rtdrv_rg_urlFilterString_add_cfg, sizeof(rtdrv_rg_urlFilterString_add_t));
			break;

		case RTDRV_RG_URLFILTERSTRING_FIND:
			copy_from_user(&buf.rtdrv_rg_urlFilterString_find_cfg, user, sizeof(rtdrv_rg_urlFilterString_find_t));
			ret = rtk_rg_urlFilterString_find(&buf.rtdrv_rg_urlFilterString_find_cfg.filter, &buf.rtdrv_rg_urlFilterString_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_urlFilterString_find_cfg, sizeof(rtdrv_rg_urlFilterString_find_t));
			break;

		case RTDRV_RG_UPNPCONNECTION_ADD:
			copy_from_user(&buf.rtdrv_rg_upnpConnection_add_cfg, user, sizeof(rtdrv_rg_upnpConnection_add_t));
			ret = rtk_rg_upnpConnection_add(&buf.rtdrv_rg_upnpConnection_add_cfg.upnp, &buf.rtdrv_rg_upnpConnection_add_cfg.upnp_idx);
			copy_to_user(user, &buf.rtdrv_rg_upnpConnection_add_cfg, sizeof(rtdrv_rg_upnpConnection_add_t));
			break;

		case RTDRV_RG_UPNPCONNECTION_FIND:
			copy_from_user(&buf.rtdrv_rg_upnpConnection_find_cfg, user, sizeof(rtdrv_rg_upnpConnection_find_t));
			ret = rtk_rg_upnpConnection_find(&buf.rtdrv_rg_upnpConnection_find_cfg.upnp, &buf.rtdrv_rg_upnpConnection_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_upnpConnection_find_cfg, sizeof(rtdrv_rg_upnpConnection_find_t));
			break;

		case RTDRV_RG_NAPTCONNECTION_ADD:
			copy_from_user(&buf.rtdrv_rg_naptConnection_add_cfg, user, sizeof(rtdrv_rg_naptConnection_add_t));
			ret = rtk_rg_naptConnection_add(&buf.rtdrv_rg_naptConnection_add_cfg.naptFlow, &buf.rtdrv_rg_naptConnection_add_cfg.flow_idx);
			copy_to_user(user, &buf.rtdrv_rg_naptConnection_add_cfg, sizeof(rtdrv_rg_naptConnection_add_t));
			break;

		case RTDRV_RG_NAPTCONNECTION_FIND:
			copy_from_user(&buf.rtdrv_rg_naptConnection_find_cfg, user, sizeof(rtdrv_rg_naptConnection_find_t));
			ret = rtk_rg_naptConnection_find(&buf.rtdrv_rg_naptConnection_find_cfg.naptInfo, &buf.rtdrv_rg_naptConnection_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_naptConnection_find_cfg, sizeof(rtdrv_rg_naptConnection_find_t));
			break;

		case RTDRV_RG_MULTICASTFLOW_ADD:
			copy_from_user(&buf.rtdrv_rg_multicastFlow_add_cfg, user, sizeof(rtdrv_rg_multicastFlow_add_t));
			ret = rtk_rg_multicastFlow_add(&buf.rtdrv_rg_multicastFlow_add_cfg.mcFlow, &buf.rtdrv_rg_multicastFlow_add_cfg.flow_idx);
			copy_to_user(user, &buf.rtdrv_rg_multicastFlow_add_cfg, sizeof(rtdrv_rg_multicastFlow_add_t));
			break;

		case RTDRV_RG_L2MULTICASTFLOW_ADD:
			copy_from_user(&buf.rtdrv_rg_l2MulticastFlow_add_cfg, user, sizeof(rtdrv_rg_l2MulticastFlow_add_t));
			ret = rtk_rg_l2MultiCastFlow_add(&buf.rtdrv_rg_l2MulticastFlow_add_cfg.l2McFlow, &buf.rtdrv_rg_l2MulticastFlow_add_cfg.flow_idx);
			copy_to_user(user, &buf.rtdrv_rg_l2MulticastFlow_add_cfg, sizeof(rtdrv_rg_l2MulticastFlow_add_t));
			break;

		case RTDRV_RG_MULTICASTFLOW_FIND:
			copy_from_user(&buf.rtdrv_rg_multicastFlow_find_cfg, user, sizeof(rtdrv_rg_multicastFlow_find_t));
			ret = rtk_rg_multicastFlow_find(&buf.rtdrv_rg_multicastFlow_find_cfg.mcFlow, &buf.rtdrv_rg_multicastFlow_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_multicastFlow_find_cfg, sizeof(rtdrv_rg_multicastFlow_find_t));
			break;

		case RTDRV_RG_MACENTRY_ADD:
			copy_from_user(&buf.rtdrv_rg_macEntry_add_cfg, user, sizeof(rtdrv_rg_macEntry_add_t));
			ret = rtk_rg_macEntry_add(&buf.rtdrv_rg_macEntry_add_cfg.macEntry, &buf.rtdrv_rg_macEntry_add_cfg.entry_idx);
			copy_to_user(user, &buf.rtdrv_rg_macEntry_add_cfg, sizeof(rtdrv_rg_macEntry_add_t));
			break;

		case RTDRV_RG_MACENTRY_FIND:
			copy_from_user(&buf.rtdrv_rg_macEntry_find_cfg, user, sizeof(rtdrv_rg_macEntry_find_t));
			ret = rtk_rg_macEntry_find(&buf.rtdrv_rg_macEntry_find_cfg.macEntry, &buf.rtdrv_rg_macEntry_find_cfg.valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_macEntry_find_cfg, sizeof(rtdrv_rg_macEntry_find_t));
			break;

		case RTDRV_RG_ARPENTRY_ADD:
			copy_from_user(&buf.rtdrv_rg_arpEntry_add_cfg, user, sizeof(rtdrv_rg_arpEntry_add_t));
			ret = rtk_rg_arpEntry_add(&buf.rtdrv_rg_arpEntry_add_cfg.arpEntry, &buf.rtdrv_rg_arpEntry_add_cfg.arp_entry_idx);
			copy_to_user(user, &buf.rtdrv_rg_arpEntry_add_cfg, sizeof(rtdrv_rg_arpEntry_add_t));
			break;

		case RTDRV_RG_ARPENTRY_FIND:
			copy_from_user(&buf.rtdrv_rg_arpEntry_find_cfg, user, sizeof(rtdrv_rg_arpEntry_find_t));
			ret = rtk_rg_arpEntry_find(&buf.rtdrv_rg_arpEntry_find_cfg.arpInfo, &buf.rtdrv_rg_arpEntry_find_cfg.arp_valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_arpEntry_find_cfg, sizeof(rtdrv_rg_arpEntry_find_t));
			break;


		case RTDRV_RG_NEIGHBORENTRY_ADD:
			copy_from_user(&buf.rtdrv_rg_neighborEntry_add_cfg, user, sizeof(rtdrv_rg_neighborEntry_add_t));
			ret = rtk_rg_neighborEntry_add(&buf.rtdrv_rg_neighborEntry_add_cfg.neighborEntry, &buf.rtdrv_rg_neighborEntry_add_cfg.neighbor_idx);
			copy_to_user(user, &buf.rtdrv_rg_neighborEntry_add_cfg, sizeof(rtdrv_rg_neighborEntry_add_t));
			break;

		case RTDRV_RG_NEIGHBORENTRY_FIND:
			copy_from_user(&buf.rtdrv_rg_neighborEntry_find_cfg, user, sizeof(rtdrv_rg_neighborEntry_find_t));
			ret = rtk_rg_neighborEntry_find(&buf.rtdrv_rg_neighborEntry_find_cfg.neighborInfo, &buf.rtdrv_rg_neighborEntry_find_cfg.neighbor_valid_idx);
			copy_to_user(user, &buf.rtdrv_rg_neighborEntry_find_cfg, sizeof(rtdrv_rg_neighborEntry_find_t));
			break;

		case RTDRV_RG_ACCESSWANLIMIT_GET:
			copy_from_user(&buf.rtdrv_rg_accessWanLimit_get_cfg, user, sizeof(rtdrv_rg_accessWanLimit_get_t));
			ret = rtk_rg_accessWanLimit_get(&buf.rtdrv_rg_accessWanLimit_get_cfg.access_wan_info);
			copy_to_user(user, &buf.rtdrv_rg_accessWanLimit_get_cfg, sizeof(rtdrv_rg_accessWanLimit_get_t));
			break;

		case RTDRV_RG_ACCESSWANLIMITCATEGORY_GET:
			copy_from_user(&buf.rtdrv_rg_accessWanLimitCategory_get_cfg, user, sizeof(rtdrv_rg_accessWanLimitCategory_get_t));
			ret = rtk_rg_accessWanLimitCategory_get(&buf.rtdrv_rg_accessWanLimitCategory_get_cfg.macCategory_info);
			copy_to_user(user, &buf.rtdrv_rg_accessWanLimitCategory_get_cfg, sizeof(rtdrv_rg_accessWanLimitCategory_get_t));
			break;

		case RTDRV_RG_SOFTWARESOURCEADDRLEARNINGLIMIT_GET:
			copy_from_user(&buf.rtdrv_rg_softwareSourceAddrLearningLimit_get_cfg, user, sizeof(rtdrv_rg_softwareSourceAddrLearningLimit_get_t));
			ret = rtk_rg_softwareSourceAddrLearningLimit_get(&buf.rtdrv_rg_softwareSourceAddrLearningLimit_get_cfg.sa_learnLimit_info, buf.rtdrv_rg_softwareSourceAddrLearningLimit_get_cfg.port_idx);
			copy_to_user(user, &buf.rtdrv_rg_softwareSourceAddrLearningLimit_get_cfg, sizeof(rtdrv_rg_softwareSourceAddrLearningLimit_get_t));
			break;

		case RTDRV_RG_WLANSOFTWARESOURCEADDRLEARNINGLIMIT_GET:
			copy_from_user(&buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_cfg, user, sizeof(rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_t));
			ret = rtk_rg_wlanSoftwareSourceAddrLearningLimit_get(&buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_cfg.sa_learnLimit_info, buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_cfg.wlan_idx, buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_cfg.dev_idx);
			copy_to_user(user, &buf.rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_cfg, sizeof(rtdrv_rg_wlanSoftwareSourceAddrLearningLimit_get_t));
			break;

		case RTDRV_RG_DOSPORTMASKENABLE_GET:
			copy_from_user(&buf.rtdrv_rg_dosPortMaskEnable_get_cfg, user, sizeof(rtdrv_rg_dosPortMaskEnable_get_t));
			ret = rtk_rg_dosPortMaskEnable_get(&buf.rtdrv_rg_dosPortMaskEnable_get_cfg.dos_port_mask);
			copy_to_user(user, &buf.rtdrv_rg_dosPortMaskEnable_get_cfg, sizeof(rtdrv_rg_dosPortMaskEnable_get_t));
			break;

		case RTDRV_RG_DOSTYPE_GET:
			copy_from_user(&buf.rtdrv_rg_dosType_get_cfg, user, sizeof(rtdrv_rg_dosType_get_t));
			ret = rtk_rg_dosType_get(buf.rtdrv_rg_dosType_get_cfg.dos_type, &buf.rtdrv_rg_dosType_get_cfg.dos_enabled, &buf.rtdrv_rg_dosType_get_cfg.dos_action);
			copy_to_user(user, &buf.rtdrv_rg_dosType_get_cfg, sizeof(rtdrv_rg_dosType_get_t));
			break;

		case RTDRV_RG_DOSFLOODTYPE_GET:
			copy_from_user(&buf.rtdrv_rg_dosFloodType_get_cfg, user, sizeof(rtdrv_rg_dosFloodType_get_t));
			ret = rtk_rg_dosFloodType_get(buf.rtdrv_rg_dosFloodType_get_cfg.dos_type, &buf.rtdrv_rg_dosFloodType_get_cfg.dos_enabled, &buf.rtdrv_rg_dosFloodType_get_cfg.dos_action, &buf.rtdrv_rg_dosFloodType_get_cfg.dos_threshold);
			copy_to_user(user, &buf.rtdrv_rg_dosFloodType_get_cfg, sizeof(rtdrv_rg_dosFloodType_get_t));
			break;


		case RTDRV_RG_PORTMIRROR_GET:
			copy_from_user(&buf.rtdrv_rg_portMirror_get_cfg, user, sizeof(rtdrv_rg_portMirror_get_t));
			ret = rtk_rg_portMirror_get(&buf.rtdrv_rg_portMirror_get_cfg.portMirrorInfo);
			copy_to_user(user, &buf.rtdrv_rg_portMirror_get_cfg, sizeof(rtdrv_rg_portMirror_get_t));
			break;

		case RTDRV_RG_PORTEGRBANDWIDTHCTRLRATE_GET:
			copy_from_user(&buf.rtdrv_rg_portEgrBandwidthCtrlRate_get_cfg, user, sizeof(rtdrv_rg_portEgrBandwidthCtrlRate_get_t));
			ret = rtk_rg_portEgrBandwidthCtrlRate_get(buf.rtdrv_rg_portEgrBandwidthCtrlRate_get_cfg.port, &buf.rtdrv_rg_portEgrBandwidthCtrlRate_get_cfg.rate);
			copy_to_user(user, &buf.rtdrv_rg_portEgrBandwidthCtrlRate_get_cfg, sizeof(rtdrv_rg_portEgrBandwidthCtrlRate_get_t));
			break;


		case RTDRV_RG_PORTIGRBANDWIDTHCTRLRATE_GET:
			copy_from_user(&buf.rtdrv_rg_portIgrBandwidthCtrlRate_get_cfg, user, sizeof(rtdrv_rg_portIgrBandwidthCtrlRate_get_t));
			ret = rtk_rg_portIgrBandwidthCtrlRate_get(buf.rtdrv_rg_portIgrBandwidthCtrlRate_get_cfg.port, &buf.rtdrv_rg_portIgrBandwidthCtrlRate_get_cfg.rate);
			copy_to_user(user, &buf.rtdrv_rg_portIgrBandwidthCtrlRate_get_cfg, sizeof(rtdrv_rg_portIgrBandwidthCtrlRate_get_t));
			break;

		case RTDRV_RG_PHYPORTFORCEABILITY_GET:
			copy_from_user(&buf.rtdrv_rg_phyPortForceAbility_get_cfg, user, sizeof(rtdrv_rg_phyPortForceAbility_get_t));
			ret = rtk_rg_phyPortForceAbility_get(buf.rtdrv_rg_phyPortForceAbility_get_cfg.port, &buf.rtdrv_rg_phyPortForceAbility_get_cfg.ability);
			copy_to_user(user, &buf.rtdrv_rg_phyPortForceAbility_get_cfg, sizeof(rtdrv_rg_phyPortForceAbility_get_t));
			break;

		case RTDRV_RG_CPUPORTFORCETRAFFICCTRL_GET:
			copy_from_user(&buf.rtdrv_rg_cpuPortForceTrafficCtrl_get_cfg, user, sizeof(rtdrv_rg_cpuPortForceTrafficCtrl_get_t));
			ret = rtk_rg_cpuPortForceTrafficCtrl_get(&buf.rtdrv_rg_cpuPortForceTrafficCtrl_get_cfg.pTx_fc_state, &buf.rtdrv_rg_cpuPortForceTrafficCtrl_get_cfg.pRx_fc_state);
			copy_to_user(user, &buf.rtdrv_rg_cpuPortForceTrafficCtrl_get_cfg, sizeof(rtdrv_rg_cpuPortForceTrafficCtrl_get_t));
			break;

		case RTDRV_RG_PORTMIBINFO_GET:
			copy_from_user(&buf.rtdrv_rg_portMibInfo_get_cfg, user, sizeof(rtdrv_rg_portMibInfo_get_t));
			ret = rtk_rg_portMibInfo_get(buf.rtdrv_rg_portMibInfo_get_cfg.port, &buf.rtdrv_rg_portMibInfo_get_cfg.mibInfo);
			copy_to_user(user, &buf.rtdrv_rg_portMibInfo_get_cfg, sizeof(rtdrv_rg_portMibInfo_get_t));
			break;

		case RTDRV_RG_PORTISOLATION_GET:
			copy_from_user(&buf.rtdrv_rg_portIsolation_get_cfg, user, sizeof(rtdrv_rg_portIsolation_get_t));
			ret = rtk_rg_portIsolation_get(&buf.rtdrv_rg_portIsolation_get_cfg.isolationSetting);
			copy_to_user(user, &buf.rtdrv_rg_portIsolation_get_cfg, sizeof(rtdrv_rg_portIsolation_get_t));
			break;

		case RTDRV_RG_STORMCONTROL_ADD:
			copy_from_user(&buf.rtdrv_rg_stormControl_add_cfg, user, sizeof(rtdrv_rg_stormControl_add_t));
			ret = rtk_rg_stormControl_add(&buf.rtdrv_rg_stormControl_add_cfg.stormInfo, &buf.rtdrv_rg_stormControl_add_cfg.stormInfo_idx);
			copy_to_user(user, &buf.rtdrv_rg_stormControl_add_cfg, sizeof(rtdrv_rg_stormControl_add_t));
			break;

		case RTDRV_RG_STORMCONTROL_FIND:
			copy_from_user(&buf.rtdrv_rg_stormControl_find_cfg, user, sizeof(rtdrv_rg_stormControl_find_t));
			ret = rtk_rg_stormControl_find(&buf.rtdrv_rg_stormControl_find_cfg.stormInfo, &buf.rtdrv_rg_stormControl_find_cfg.stormInfo_idx);
			copy_to_user(user, &buf.rtdrv_rg_stormControl_find_cfg, sizeof(rtdrv_rg_stormControl_find_t));
			break;

		case RTDRV_RG_SHAREMETER_GET:
			copy_from_user(&buf.rtdrv_rg_shareMeter_get_cfg, user, sizeof(rtdrv_rg_shareMeter_get_t));
			ret = rtk_rg_shareMeter_get(buf.rtdrv_rg_shareMeter_get_cfg.index, &buf.rtdrv_rg_shareMeter_get_cfg.pRate, &buf.rtdrv_rg_shareMeter_get_cfg.pIfgInclude);
			copy_to_user(user, &buf.rtdrv_rg_shareMeter_get_cfg, sizeof(rtdrv_rg_shareMeter_get_t));
			break;

		case RTDRV_RG_QOSSTRICTPRIORITYORWEIGHTFAIRQUEUE_GET:
			copy_from_user(&buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_cfg, user, sizeof(rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_t));
			ret = rtk_rg_qosStrictPriorityOrWeightFairQueue_get(buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_cfg.port_idx, &buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_cfg.pQ_weight);
			copy_to_user(user, &buf.rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_cfg, sizeof(rtdrv_rg_qosStrictPriorityOrWeightFairQueue_get_t));
			break;

		case RTDRV_RG_QOSINTERNALPRIMAPTOQUEUEID_GET:
			copy_from_user(&buf.rtdrv_rg_qosInternalPriMapToQueueId_get_cfg, user, sizeof(rtdrv_rg_qosInternalPriMapToQueueId_get_t));
			ret = rtk_rg_qosInternalPriMapToQueueId_get(buf.rtdrv_rg_qosInternalPriMapToQueueId_get_cfg.intPri,&buf.rtdrv_rg_qosInternalPriMapToQueueId_get_cfg.pQueueId);
			copy_to_user(user, &buf.rtdrv_rg_qosInternalPriMapToQueueId_get_cfg, sizeof(rtdrv_rg_qosInternalPriMapToQueueId_get_t));
			break;

		case RTDRV_RG_QOSINTERNALPRIDECISIONBYWEIGHT_GET:
			copy_from_user(&buf.rtdrv_rg_qosInternalPriDecisionByWeight_get_cfg, user, sizeof(rtdrv_rg_qosInternalPriDecisionByWeight_get_t));
			ret = rtk_rg_qosInternalPriDecisionByWeight_get(&buf.rtdrv_rg_qosInternalPriDecisionByWeight_get_cfg.pWeightOfPriSel);
			copy_to_user(user, &buf.rtdrv_rg_qosInternalPriDecisionByWeight_get_cfg, sizeof(rtdrv_rg_qosInternalPriDecisionByWeight_get_t));
			break;

		case RTDRV_RG_QOSDSCPREMAPTOINTERNALPRI_GET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemapToInternalPri_get_cfg, user, sizeof(rtdrv_rg_qosDscpRemapToInternalPri_get_t));
			ret = rtk_rg_qosDscpRemapToInternalPri_get(buf.rtdrv_rg_qosDscpRemapToInternalPri_get_cfg.dscp, &buf.rtdrv_rg_qosDscpRemapToInternalPri_get_cfg.pIntPri);
			copy_to_user(user, &buf.rtdrv_rg_qosDscpRemapToInternalPri_get_cfg, sizeof(rtdrv_rg_qosDscpRemapToInternalPri_get_t));
			break;

		case RTDRV_RG_QOSDOT1PPRIREMAPTOINTERNALPRI_GET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_get_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemapToInternalPri_get_t));
			ret = rtk_rg_qosDot1pPriRemapToInternalPri_get(buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_get_cfg.dot1p, &buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_get_cfg.pIntPri);
			copy_to_user(user, &buf.rtdrv_rg_qosDot1pPriRemapToInternalPri_get_cfg, sizeof(rtdrv_rg_qosDot1pPriRemapToInternalPri_get_t));
			break;

		case RTDRV_RG_QOSPORTBASEDPRIORITY_GET:
			copy_from_user(&buf.rtdrv_rg_qosPortBasedPriority_get_cfg, user, sizeof(rtdrv_rg_qosPortBasedPriority_get_t));
			ret = rtk_rg_qosPortBasedPriority_get(buf.rtdrv_rg_qosPortBasedPriority_get_cfg.port, &buf.rtdrv_rg_qosPortBasedPriority_get_cfg.pIntPri);
			copy_to_user(user, &buf.rtdrv_rg_qosPortBasedPriority_get_cfg, sizeof(rtdrv_rg_qosPortBasedPriority_get_t));
			break;

		case RTDRV_RG_QOSDSCPREMARKEGRESSPORTENABLEANDSRCSELECT_GET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_t));
			ret = rtk_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get(buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_cfg.port,&buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_cfg.pIs_enabled, &buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_set_cfg.src_sel);
			copy_to_user(user, &buf.rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_cfg, sizeof(rtdrv_rg_qosDscpRemarkEgressPortEnableAndSrcSelect_get_t));
			break;

		case RTDRV_RG_QOSDSCPREMARKBYINTERNALPRI_GET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkByInternalPri_get_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkByInternalPri_get_t));
			ret = rtk_rg_qosDscpRemarkByInternalPri_get(buf.rtdrv_rg_qosDscpRemarkByInternalPri_get_cfg.int_pri, &buf.rtdrv_rg_qosDscpRemarkByInternalPri_get_cfg.pRmk_dscp);
			copy_to_user(user, &buf.rtdrv_rg_qosDscpRemarkByInternalPri_get_cfg, sizeof(rtdrv_rg_qosDscpRemarkByInternalPri_get_t));
			break;

		case RTDRV_RG_QOSDSCPREMARKBYDSCP_GET:
			copy_from_user(&buf.rtdrv_rg_qosDscpRemarkByDscp_get_cfg, user, sizeof(rtdrv_rg_qosDscpRemarkByDscp_get_t));
			ret = rtk_rg_qosDscpRemarkByDscp_get(buf.rtdrv_rg_qosDscpRemarkByDscp_get_cfg.dscp, &buf.rtdrv_rg_qosDscpRemarkByDscp_get_cfg.pRmk_dscp);
			copy_to_user(user, &buf.rtdrv_rg_qosDscpRemarkByDscp_get_cfg, sizeof(rtdrv_rg_qosDscpRemarkByDscp_get_t));
			break;

		case RTDRV_RG_QOSDOT1PPRIREMARKBYINTERNALPRIEGRESSPORTENABLE_GET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_t));
			ret = rtk_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get(buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_cfg.port,&buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_cfg.pEnable);
			copy_to_user(user, &buf.rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_cfg, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPriEgressPortEnable_get_t));
			break;

		case RTDRV_RG_QOSDOT1PPRIREMARKBYINTERNALPRI_GET:
			copy_from_user(&buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_cfg, user, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_t));
			ret = rtk_rg_qosDot1pPriRemarkByInternalPri_get(buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_cfg.int_pri, &buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_cfg.pRmk_dot1p);
			copy_to_user(user, &buf.rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_cfg, sizeof(rtdrv_rg_qosDot1pPriRemarkByInternalPri_get_t));
			break;

		case RTDRV_RG_PORTBASEDCVLANID_GET:
			copy_from_user(&buf.rtdrv_rg_portBasedCVlanId_get_cfg, user, sizeof(rtdrv_rg_portBasedCVlanId_get_t));
			ret = rtk_rg_portBasedCVlanId_get(buf.rtdrv_rg_portBasedCVlanId_get_cfg.port_idx, &buf.rtdrv_rg_portBasedCVlanId_get_cfg.pPvid);
			copy_to_user(user, &buf.rtdrv_rg_portBasedCVlanId_get_cfg, sizeof(rtdrv_rg_portBasedCVlanId_get_t));
			break;

		case RTDRV_RG_WLANDEVBASEDCVLANID_GET:
			copy_from_user(&buf.rtdrv_rg_wlanDevBasedCVlanId_get_cfg, user, sizeof(rtdrv_rg_wlanDevBasedCVlanId_get_t));
			ret = rtk_rg_wlanDevBasedCVlanId_get(buf.rtdrv_rg_wlanDevBasedCVlanId_get_cfg.wlan_idx, buf.rtdrv_rg_wlanDevBasedCVlanId_get_cfg.dev_idx, &buf.rtdrv_rg_wlanDevBasedCVlanId_get_cfg.pDvid);
			copy_to_user(user, &buf.rtdrv_rg_wlanDevBasedCVlanId_get_cfg, sizeof(rtdrv_rg_wlanDevBasedCVlanId_get_t));
			break;

		case RTDRV_RG_PORTSTATUS_GET:
			copy_from_user(&buf.rtdrv_rg_portStatus_get_cfg, user, sizeof(rtdrv_rg_portStatus_get_t));
			ret = rtk_rg_portStatus_get(buf.rtdrv_rg_portStatus_get_cfg.port, &buf.rtdrv_rg_portStatus_get_cfg.portInfo);
			copy_to_user(user, &buf.rtdrv_rg_portStatus_get_cfg, sizeof(rtdrv_rg_portStatus_get_t));
			break;

		case RTDRV_RG_CLASSIFYENTRY_ADD:
			copy_from_user(&buf.rtdrv_rg_classifyEntry_add_cfg, user, sizeof(rtdrv_rg_classifyEntry_add_t));
			ret = rtk_rg_classifyEntry_add(&buf.rtdrv_rg_classifyEntry_add_cfg.classifyFilter);
			copy_to_user(user, &buf.rtdrv_rg_classifyEntry_add_cfg, sizeof(rtdrv_rg_classifyEntry_add_t));
			break;

		case RTDRV_RG_CLASSIFYENTRY_FIND:
			copy_from_user(&buf.rtdrv_rg_classifyEntry_find_cfg, user, sizeof(rtdrv_rg_classifyEntry_find_t));
			ret = rtk_rg_classifyEntry_find(buf.rtdrv_rg_classifyEntry_find_cfg.index, &buf.rtdrv_rg_classifyEntry_find_cfg.classifyFilter);
			copy_to_user(user, &buf.rtdrv_rg_classifyEntry_find_cfg, sizeof(rtdrv_rg_classifyEntry_find_t));
			break;

		case RTDRV_RG_PPPOEINTERFACEIDLETIME_GET:
			copy_from_user(&buf.rtdrv_rg_pppoeInterfaceIdleTime_get_cfg, user, sizeof(rtdrv_rg_pppoeInterfaceIdleTime_get_t));
			ret = rtk_rg_pppoeInterfaceIdleTime_get(buf.rtdrv_rg_pppoeInterfaceIdleTime_get_cfg.intfIdx, &buf.rtdrv_rg_pppoeInterfaceIdleTime_get_cfg.idleSec);
			copy_to_user(user, &buf.rtdrv_rg_pppoeInterfaceIdleTime_get_cfg, sizeof(rtdrv_rg_pppoeInterfaceIdleTime_get_t));
			break;

		case RTDRV_RG_GATEWAYSERVICEPORTREGISTER_ADD:
			copy_from_user(&buf.rtdrv_rg_gatewayServicePortRegister_add_cfg, user, sizeof(rtdrv_rg_gatewayServicePortRegister_add_t));
			ret = rtk_rg_gatewayServicePortRegister_add(&buf.rtdrv_rg_gatewayServicePortRegister_add_cfg.serviceEntry, &buf.rtdrv_rg_gatewayServicePortRegister_add_cfg.index);
			copy_to_user(user, &buf.rtdrv_rg_gatewayServicePortRegister_add_cfg, sizeof(rtdrv_rg_gatewayServicePortRegister_add_t));
			break;

		case RTDRV_RG_GATEWAYSERVICEPORTREGISTER_FIND:
			copy_from_user(&buf.rtdrv_rg_gatewayServicePortRegister_find_cfg, user, sizeof(rtdrv_rg_gatewayServicePortRegister_find_t));
			ret = rtk_rg_gatewayServicePortRegister_find(&buf.rtdrv_rg_gatewayServicePortRegister_find_cfg.serviceEntry, &buf.rtdrv_rg_gatewayServicePortRegister_find_cfg.index);
			copy_to_user(user, &buf.rtdrv_rg_gatewayServicePortRegister_find_cfg, sizeof(rtdrv_rg_gatewayServicePortRegister_find_t));
			break;

		case RTDRV_RG_GPONDSBCFILTERANDREMARKING_ADD:
			 copy_from_user(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_add_cfg, user, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_add_t));
			 ret = rtk_rg_gponDsBcFilterAndRemarking_add(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_add_cfg.filterRule, &buf.rtdrv_rg_gponDsBcFilterAndRemarking_add_cfg.index);
			 copy_to_user(user, &buf.rtdrv_rg_gponDsBcFilterAndRemarking_add_cfg, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_add_t));
			 break;

		case RTDRV_RG_GPONDSBCFILTERANDREMARKING_FIND:
			 copy_from_user(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_find_cfg, user, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_find_t));
			 ret = rtk_rg_gponDsBcFilterAndRemarking_find(&buf.rtdrv_rg_gponDsBcFilterAndRemarking_find_cfg.index, &buf.rtdrv_rg_gponDsBcFilterAndRemarking_find_cfg.filterRule);
			 copy_to_user(user, &buf.rtdrv_rg_gponDsBcFilterAndRemarking_find_cfg, sizeof(rtdrv_rg_gponDsBcFilterAndRemarking_find_t));
			 break;

		case RTDRV_RG_STPBLOCKINGPORTMASK_GET:
			copy_from_user(&buf.rtdrv_rg_stpBlockingPortmask_get_cfg, user, sizeof(rtdrv_rg_stpBlockingPortmask_get_t));
			ret = rtk_rg_stpBlockingPortmask_get(&buf.rtdrv_rg_stpBlockingPortmask_get_cfg.Mask);
			copy_to_user(user, &buf.rtdrv_rg_stpBlockingPortmask_get_cfg, sizeof(rtdrv_rg_stpBlockingPortmask_get_t));
			break;

		case RTDRV_RG_DSLITEMCTABLE_SET:
			copy_from_user(&buf.rtdrv_rg_dsliteMcTable_set_cfg, user, sizeof(rtdrv_rg_dsliteMcTable_set_t));
			ret = rtk_rg_dsliteMcTable_set(&buf.rtdrv_rg_dsliteMcTable_set_cfg.pDsliteMcEntry);
			copy_to_user(user, &buf.rtdrv_rg_dsliteMcTable_set_cfg, sizeof(rtdrv_rg_dsliteMcTable_set_t));
			break;

		case RTDRV_RG_DSLITEMCTABLE_GET:
			copy_from_user(&buf.rtdrv_rg_dsliteMcTable_get_cfg, user, sizeof(rtdrv_rg_dsliteMcTable_get_t));
			ret = rtk_rg_dsliteMcTable_get(&buf.rtdrv_rg_dsliteMcTable_get_cfg.pDsliteMcEntry);
			copy_to_user(user, &buf.rtdrv_rg_dsliteMcTable_get_cfg, sizeof(rtdrv_rg_dsliteMcTable_get_t));
			break;

		case RTDRV_RG_DSLITECONTROL_GET:
			copy_from_user(&buf.rtdrv_rg_dsliteControl_get_cfg, user, sizeof(rtdrv_rg_dsliteControl_get_t));
			ret = rtk_rg_dsliteControl_get(buf.rtdrv_rg_dsliteControl_get_cfg.ctrlType, &buf.rtdrv_rg_dsliteControl_get_cfg.pAct);
			copy_to_user(user, &buf.rtdrv_rg_dsliteControl_get_cfg, sizeof(rtdrv_rg_dsliteControl_get_t));
			break;

		case RTDRV_RG_INTERFACEMIBCOUNTER_GET:
			copy_from_user(&buf.rtdrv_rg_interfaceMibCounter_get_cfg, user, sizeof(rtdrv_rg_interfaceMibCounter_get_t));
			ret = rtk_rg_interfaceMibCounter_get(&buf.rtdrv_rg_interfaceMibCounter_get_cfg.pMibCnt);
			copy_to_user(user, &buf.rtdrv_rg_interfaceMibCounter_get_cfg, sizeof(rtdrv_rg_interfaceMibCounter_get_t));
			break;

		case RTDRV_RG_REDIRECTHTTPALL_SET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpAll_set_cfg, user, sizeof(rtdrv_rg_redirectHttpAll_set_t));
			ret = rtk_rg_redirectHttpAll_set(&buf.rtdrv_rg_redirectHttpAll_set_cfg.pRedirectHttpAll);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpAll_set_cfg, sizeof(rtdrv_rg_redirectHttpAll_set_t));
			break;

		case RTDRV_RG_REDIRECTHTTPALL_GET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpAll_get_cfg, user, sizeof(rtdrv_rg_redirectHttpAll_get_t));
			ret = rtk_rg_redirectHttpAll_get(&buf.rtdrv_rg_redirectHttpAll_get_cfg.pRedirectHttpAll);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpAll_get_cfg, sizeof(rtdrv_rg_redirectHttpAll_get_t));
			break;

		case RTDRV_RG_REDIRECTHTTPURL_ADD:
			copy_from_user(&buf.rtdrv_rg_redirectHttpURL_add_cfg, user, sizeof(rtdrv_rg_redirectHttpURL_add_t));
			ret = rtk_rg_redirectHttpURL_add(&buf.rtdrv_rg_redirectHttpURL_add_cfg.pRedirectHttpURL);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpURL_add_cfg, sizeof(rtdrv_rg_redirectHttpURL_add_t));
			break;

		case RTDRV_RG_REDIRECTHTTPURL_DEL:
			copy_from_user(&buf.rtdrv_rg_redirectHttpURL_del_cfg, user, sizeof(rtdrv_rg_redirectHttpURL_del_t));
			ret = rtk_rg_redirectHttpURL_del(&buf.rtdrv_rg_redirectHttpURL_del_cfg.pRedirectHttpURL);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpURL_del_cfg, sizeof(rtdrv_rg_redirectHttpURL_del_t));
			break;

		case RTDRV_RG_REDIRECTHTTPWHITELIST_ADD:
			copy_from_user(&buf.rtdrv_rg_redirectHttpWhiteList_add_cfg, user, sizeof(rtdrv_rg_redirectHttpWhiteList_add_t));
			ret = rtk_rg_redirectHttpWhiteList_add(&buf.rtdrv_rg_redirectHttpWhiteList_add_cfg.pRedirectHttpWhiteList);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpWhiteList_add_cfg, sizeof(rtdrv_rg_redirectHttpWhiteList_add_t));
			break;

		case RTDRV_RG_REDIRECTHTTPWHITELIST_DEL:
			copy_from_user(&buf.rtdrv_rg_redirectHttpWhiteList_del_cfg, user, sizeof(rtdrv_rg_redirectHttpWhiteList_del_t));
			ret = rtk_rg_redirectHttpWhiteList_del(&buf.rtdrv_rg_redirectHttpWhiteList_del_cfg.pRedirectHttpWhiteList);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpWhiteList_del_cfg, sizeof(rtdrv_rg_redirectHttpWhiteList_del_t));
			break;

		case RTDRV_RG_REDIRECTHTTPRSP_SET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpRsp_set_cfg, user, sizeof(rtdrv_rg_redirectHttpRsp_set_t));
			ret = rtk_rg_redirectHttpRsp_set(&buf.rtdrv_rg_redirectHttpRsp_set_cfg.pRedirectHttpRsp);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpRsp_set_cfg, sizeof(rtdrv_rg_redirectHttpRsp_set_t));
			break;

		case RTDRV_RG_REDIRECTHTTPRSP_GET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpRsp_get_cfg, user, sizeof(rtdrv_rg_redirectHttpRsp_get_t));
			ret = rtk_rg_redirectHttpRsp_get(&buf.rtdrv_rg_redirectHttpRsp_get_cfg.pRedirectHttpRsp);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpRsp_get_cfg, sizeof(rtdrv_rg_redirectHttpRsp_get_t));
			break;

		case RTDRV_RG_SVLANTPID2_ENABLE_GET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid2_enable_get_cfg, user, sizeof(rtdrv_rg_svlanTpid2_enable_get_t));
			ret = rtk_rg_svlanTpid2_enable_get(&buf.rtdrv_rg_svlanTpid2_enable_get_cfg.pEnable);
			copy_to_user(user, &buf.rtdrv_rg_svlanTpid2_enable_get_cfg, sizeof(rtdrv_rg_svlanTpid2_enable_get_t));
			break;
		
		case RTDRV_RG_SVLANTPID2_GET:
			copy_from_user(&buf.rtdrv_rg_svlanTpid2_get_cfg, user, sizeof(rtdrv_rg_svlanTpid2_get_t));
			ret = rtk_rg_svlanTpid2_get(&buf.rtdrv_rg_svlanTpid2_get_cfg.pSvlanTagId);
			copy_to_user(user, &buf.rtdrv_rg_svlanTpid2_get_cfg, sizeof(rtdrv_rg_svlanTpid2_get_t));
			break;

		case RTDRV_RG_HOSTPOLICECONTROL_SET:
			copy_from_user(&buf.rtdrv_rg_hostPoliceControl_set_cfg, user, sizeof(rtdrv_rg_hostPoliceControl_set_t));
			ret = rtk_rg_hostPoliceControl_set(&buf.rtdrv_rg_hostPoliceControl_set_cfg.pHostPoliceControl, buf.rtdrv_rg_hostPoliceControl_set_cfg.host_idx);
			copy_to_user(user, &buf.rtdrv_rg_hostPoliceControl_set_cfg, sizeof(rtdrv_rg_hostPoliceControl_set_t));
			break;

		case RTDRV_RG_HOSTPOLICECONTROL_GET:
			copy_from_user(&buf.rtdrv_rg_hostPoliceControl_get_cfg, user, sizeof(rtdrv_rg_hostPoliceControl_get_t));
			ret = rtk_rg_hostPoliceControl_get(&buf.rtdrv_rg_hostPoliceControl_get_cfg.pHostPoliceControl, buf.rtdrv_rg_hostPoliceControl_get_cfg.host_idx);
			copy_to_user(user, &buf.rtdrv_rg_hostPoliceControl_get_cfg, sizeof(rtdrv_rg_hostPoliceControl_get_t));
			break;

		case RTDRV_RG_HOSTPOLICELOGGING_GET:
			copy_from_user(&buf.rtdrv_rg_hostPoliceLogging_get_cfg, user, sizeof(rtdrv_rg_hostPoliceLogging_get_t));
			ret = rtk_rg_hostPoliceLogging_get(&buf.rtdrv_rg_hostPoliceLogging_get_cfg.pHostMibCnt, buf.rtdrv_rg_hostPoliceLogging_get_cfg.host_idx);
			copy_to_user(user, &buf.rtdrv_rg_hostPoliceLogging_get_cfg, sizeof(rtdrv_rg_hostPoliceLogging_get_t));
			break;

		case RTDRV_RG_REDIRECTHTTPCOUNT_SET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpCount_set_cfg, user, sizeof(rtdrv_rg_redirectHttpCount_set_t));
			ret = rtk_rg_redirectHttpCount_set(&buf.rtdrv_rg_redirectHttpCount_set_cfg.pRedirectHttpCount);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpCount_set_cfg, sizeof(rtdrv_rg_redirectHttpCount_set_t));
			break;

		case RTDRV_RG_REDIRECTHTTPCOUNT_GET:
			copy_from_user(&buf.rtdrv_rg_redirectHttpCount_get_cfg, user, sizeof(rtdrv_rg_redirectHttpCount_get_t));
			ret = rtk_rg_redirectHttpCount_get(&buf.rtdrv_rg_redirectHttpCount_get_cfg.pRedirectHttpCount);
			copy_to_user(user, &buf.rtdrv_rg_redirectHttpCount_get_cfg, sizeof(rtdrv_rg_redirectHttpCount_get_t));
			break;
		
		case RTDRV_RG_STATICROUTE_ADD:
			copy_from_user(&buf.rtdrv_rg_staticRoute_add_cfg, user, sizeof(rtdrv_rg_staticRoute_add_t));
			ret = rtk_rg_staticRoute_add(&buf.rtdrv_rg_staticRoute_add_cfg.pStaticRoute, &buf.rtdrv_rg_staticRoute_add_cfg.index);
			copy_to_user(user, &buf.rtdrv_rg_staticRoute_add_cfg, sizeof(rtdrv_rg_staticRoute_add_t));
			break;
		
		case RTDRV_RG_STATICROUTE_FIND:
			copy_from_user(&buf.rtdrv_rg_staticRoute_find_cfg, user, sizeof(rtdrv_rg_staticRoute_find_t));
			ret = rtk_rg_staticRoute_find(&buf.rtdrv_rg_staticRoute_find_cfg.pStaticRoute, &buf.rtdrv_rg_staticRoute_find_cfg.index);
			copy_to_user(user, &buf.rtdrv_rg_staticRoute_find_cfg, sizeof(rtdrv_rg_staticRoute_find_t));
			break;
#endif


    }
	return ret;

}
