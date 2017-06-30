//
//  myfuncs1.h
//  ctest
//
//  Created by Steven Webb on 05/04/2017.
//  Copyright © 2017 Steven Webb. All rights reserved.
//

#ifndef myfuncs1_h
#define myfuncs1_h

#include <stdio.h>

#endif /* myfuncs1_h */
#define AUTHOR "Steve Webb"
#define MAX_SCREEN_LINES 60
#define NEW_LINE 0x0a
#define BUFFER_WIDTH_MAX 200
#define MENU_OPTIONS 11
#define MAX_NO_LINES 10000
#define NOT_FOUND -1
#define FAN_LINES 8 //number of lines to display before stopping
#define SPACE 32

#define DBG 0
#define MENU_LIST "Commands are:\n\nsystem,mac,vlan,ipint,arp,pvid,intstat,\
intcount,route,ospfnei,ospfroute,ospfinfo\
rf,sensors,fans,http,icf,lic,licuse,lldp,lldpnei,logging,manage,manuf,synce,\
prot,info,cls,help,?,quit";
#define SWITCH_PROMPT "set switch-name"//changes needed because of switch name change
#define SWITCH_PROMPT_ENABLE "set prompt switch-name enable"

//#define SWITCH_PROMPT "show vfi"

#define STOP "aos#"
#define SYS_INFO "show system information"
#define MAC_TABLE "show mac-address-table"
#define VLAN_TABLE "show vlan"
#define INT_STATUS "show interface status"
#define INT_STATUSS "show interfaces status"
#define INT_COUNTERS "show interface counters"
#define INT_COUNTERSS "show interfaces counters"
#define RF_LINK "show radio link"
#define SENSOR_TABLE "show sensor"
#define VLAN_PVID "show service vlan"
#define SYS_DETAILS "show system information"
#define HTTP_SERVER "show http server status"
#define ICF_STATUS "show icf"
#define IP_ARP "show ip arp"
#define IP_INT "show ip interface"
#define IP_ROUTE "show ip route"
#define OSPF_NEIGH "show ip ospf neighbor"
#define OSPF_ROUTE "show ip ospf route"
#define LIC "show license"
#define LIC_USE "show license usage"
#define LLDP_INFO "show lldp"
#define LLDP_NEI "show lldp neighbors detail"
#define LOGGING "show logging"
#define MANAGE "show management"
#define MANUF "show manufacture-details"
#define SYNCE "show network-clock"
#define PROT "show protection"
#define ROUTER_OSPF "router ospf"


struct FileDetails{
    char* nameOfFile;
    unsigned int noOfLinesInFile;
};
struct ChassisInfo{
    char switchName[254];
    char swVersion[30];
    char upTime[30];
};

//Declare prototypes
void debug(char* msg);
void cls(void);
unsigned int totalLinesInFile(FILE *file);
int menu(void);
int showSection(FILE *file, char* searchString, char* stopString);
fpos_t findStart(FILE *file, char* search);
int findSwitchPrompt(FILE *file, char* CtrPrompt);
int showInfo(FILE *file, struct ChassisInfo *chassisInfo, struct FileDetails fileDetails);

//All the functions for the helpdesk file
int showMACTable(FILE *file, char* CtrPrompt);
int showVLANTable(FILE *file, char* CtrPrompt);
int showIpTable(FILE *file, char* CtrPrompt);
int showIntStatusTable(FILE *file, char* CtrPrompt);
int showIntCountTable(FILE *file, char* CtrPrompt);
int showRfTable(FILE *file, char* CtrPrompt);
int showSensorTable(FILE *file, char* CtrPrompt);
int showVLANPvidTable(FILE *file, char* CtrPrompt);
int showFans(FILE *file, char* CtrPrompt);
int showSystem(FILE *file, char* CtrPrompt);
int showHTTPServer(FILE *file, char* CtrPrompt);
int showICFStatus(FILE *file, char* CtrPrompt);
int showIPArp(FILE *file, char* CtrPrompt);
int showIPInt(FILE *file, char* CtrPrompt);
int showIPRoute(FILE *file, char* CtrPrompt);
int showOSPFNeigh(FILE *file, char* CtrPrompt);
int showOSPFRoute(FILE *file, char* CtrPrompt);
int showLIC(FILE *file, char* CtrPrompt);
int showLICUse(FILE *file, char* CtrPrompt);
int showLLDPInfo(FILE *file, char* CtrPrompt);
int showLLDPNei(FILE *file, char* CtrPrompt);
int showLogging(FILE *file, char* CtrPrompt);
int showManagement(FILE *file, char* CtrPrompt);
int showManufacture(FILE *file, char* CtrPrompt);
int showSyncE(FILE *file, char* CtrPrompt);
int showProtection(FILE *file, char* CtrPrompt);
int showOSPFRoute(FILE *file, char* CtrPrompt);

