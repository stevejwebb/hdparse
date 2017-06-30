//
//  main.c
//  ctest
//
//  Created by Steven Webb on 17/03/2017.
//  Copyright © 2017 Steven Webb. All rights reserved.
//
#define END "End of the program"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "myfuncs1.h"
#define TEMP_FILENAME "aosInfo.txt"
char *CtrPrompt;

int main(int argc, const char * argv[]) {
    FILE *file;
    //int lengthOfSwitchPrompt = 0;
    char fileName[100];
    struct FileDetails fileDetails;
    struct ChassisInfo *chassisInfo;
    char menuChoice[20];
    bool fileOK = false;
    //char *CtrPrompt;
    CtrPrompt = (char*)malloc(sizeof(100));
    memset(CtrPrompt, 0, 100);
    strcpy(CtrPrompt, "aos#");
    chassisInfo = (struct ChassisInfo*) malloc(sizeof(struct ChassisInfo)); //allocate memory for this structure
    //if no filename specified in arguments then default to aosInfo.txt
    if (argc >= 2) strcpy(fileName, argv[1]);
    else strcpy(fileName, "aosInfo.txt");
    cls();
    //try to open the file
    if ((file = fopen(fileName, "r")) == NULL)
    {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }else fileOK = true;
    fileDetails.nameOfFile = fileName;
    fileDetails.noOfLinesInFile = totalLinesInFile(file);
    //Sanity check less than 5000 lines flag warning
    if (fileDetails.noOfLinesInFile <= 5000) printf("\n*** Warning: only %d lines in this file! ***\n\n",fileDetails.noOfLinesInFile);
    findSwitchPrompt(file, CtrPrompt);
    strcpy(chassisInfo->switchName, CtrPrompt);
    
    printf("File open: %s\n",fileDetails.nameOfFile);
    printf("Number of lines in file: %u\n",fileDetails.noOfLinesInFile);
    printf("CTR Switch Name: %s\n",CtrPrompt);
    printf("\n");
    
    menu();
    while (true) {
        printf("Command: ");
        scanf("%20s",menuChoice);
        if (strcmp(menuChoice,"quit") == 0) break;
        else if (strcmp(menuChoice,"q") == 0) break;
        else if (strcmp(menuChoice,"cls") == 0) cls();
        else if (strcmp(menuChoice,"help") == 0) menu();
        else if (strcmp(menuChoice,"?") == 0) menu();
        else if (strcmp(menuChoice,"mac") == 0) showMACTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"vlan") == 0) showVLANTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"pvid") == 0) showVLANPvidTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"intstat") == 0) showIntStatusTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"intcount") == 0) showIntCountTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"rf") == 0) showRfTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"sensors") == 0) showSensorTable(file, CtrPrompt);
        else if (strcmp(menuChoice,"system") == 0) showSystem(file, CtrPrompt);
        else if (strcmp(menuChoice,"fans") == 0) showFans(file, CtrPrompt);
        else if (strcmp(menuChoice,"http") == 0) showHTTPServer(file, CtrPrompt);
        else if (strcmp(menuChoice,"icf") == 0) showICFStatus(file, CtrPrompt);
        else if (strcmp(menuChoice,"arp") == 0) showIPArp(file, CtrPrompt);
        else if (strcmp(menuChoice,"ipint") == 0) showIPInt(file, CtrPrompt);
        else if (strcmp(menuChoice,"route") == 0) showIPRoute(file, CtrPrompt);
        else if (strcmp(menuChoice,"ospfnei") == 0) showOSPFNeigh(file, CtrPrompt);
        else if (strcmp(menuChoice,"ospfroute") == 0) showOSPFRoute(file, CtrPrompt);
        else if (strcmp(menuChoice,"lic") == 0) showLIC(file, CtrPrompt);
        else if (strcmp(menuChoice,"licuse") == 0) showLICUse(file, CtrPrompt);
        else if (strcmp(menuChoice,"lldpinfo") == 0) showLLDPInfo(file, CtrPrompt);
        else if (strcmp(menuChoice,"lldpnei") == 0) showLLDPNei(file, CtrPrompt);
        else if (strcmp(menuChoice,"logging") == 0) showLogging(file, CtrPrompt);
        else if (strcmp(menuChoice,"manage") == 0) showManagement(file, CtrPrompt);
        else if (strcmp(menuChoice,"manuf") == 0) showManufacture(file, CtrPrompt);
        else if (strcmp(menuChoice,"synce") == 0) showSyncE(file, CtrPrompt);
        else if (strcmp(menuChoice,"prot") == 0) showProtection(file, CtrPrompt);
        else if (strcmp(menuChoice,"prot") == 0) showOSPFRoute(file, CtrPrompt);
        else if (strcmp(menuChoice,"info") == 0) showInfo(file, chassisInfo, fileDetails);
        
    }
    
    //Tidy up
    
    printf("\n");
    fclose(file);
    return 0;
}

