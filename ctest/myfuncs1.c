//
//  myfuncs1.c
//  ctest
//
//  Created by Steven Webb on 05/04/2017.
//  Copyright © 2017 Steven Webb. All rights reserved.
//

#include "myfuncs1.h"
#include <string.h>
#include <stdlib.h>


void debug(char* msg)
{
    if(!DBG) return; //debug off
    printf("\n%s\n",msg);
    return;
}
void cls(void){
    int x;
    for (x=0;x<=MAX_SCREEN_LINES;x++) printf("\n");
}
int menu(void)
{//display and process menu options
    char* menuOptions = MENU_LIST;
    int offSet = 0, lineBreak=0;
    for (offSet=0; offSet<=strlen(menuOptions); offSet++) {
        if (menuOptions[offSet] == ',') {
            printf("\t");
            if (lineBreak >=5) {
                printf("\n");
                lineBreak = 0;
            }
            lineBreak++;
            continue;
        }
        printf("%c",menuOptions[offSet]);
    }
    printf("\n\n");
    return 0;
}
unsigned int totalLinesInFile(FILE *file)
{//return the number of lines in the file
    unsigned int noOfLines = 0;
    int testCharacter;
    fpos_t filePosition;
    fgetpos(file, &filePosition);//save the position
    
    rewind(file); //go to begining
    while ((testCharacter = getc(file)) != EOF) if (testCharacter == NEW_LINE) noOfLines++;
    fsetpos(file, &filePosition);//restore the position
    return noOfLines;
}
int findSwitchPrompt(FILE *file, char* CtrPrompt)
{//find the command to enable the command prompt
    fpos_t check = 0;
    char buffer[100];
    memset(buffer, 0, sizeof(buffer));
    //Need to see if prompt is still AOS# or something else
    //see if it has been changed and enabled
    check = findStart(file, SWITCH_PROMPT_ENABLE);
    if (check == NOT_FOUND) return NOT_FOUND;
    check = findStart(file, SWITCH_PROMPT);//look for command to change switch prompt
    if (check == NOT_FOUND)
    {
        printf("Cannot find switch prompt find: %lld\n",check);
        
    }
    else
    {
        fpos_t filePosition;
        fgetpos(file, &filePosition);
        int check = -1;
        int offSet = 0;
        char c = ' ';
        while (1) {
            check = fgetc(file);
            fsetpos(file, &filePosition);
            filePosition--;
            if (check == SPACE) break;//found beginning of prompt name
        }
        filePosition +=3;
        fsetpos(file, &filePosition);//move past the space
        while (1)
        {
            //need to copy prompt to CtrPrompt
            c = getc(file);
            if (c == '\n') break;
            buffer[offSet] = c;
            offSet++;
        }
        //add the hash to the end
        buffer[offSet] = '#';
        strcpy(CtrPrompt, buffer);
    }
    return 0;
}
int showSection(FILE *file, char* searchString, char* stopString)
{//********ignore switch name***************
    char buffer[BUFFER_WIDTH_MAX];
    int character, offset = 0, lineCount = 0;
    fpos_t filePosition = 0; //*****Offset to ignore the switch prompt, either AOS# or switch name
    filePosition = findStart(file, searchString);
    if (filePosition <=0) return NOT_FOUND;//not found
    fsetpos(file, &filePosition);
    while (1) {//print until you reach the stop string
        memset(buffer, 0, BUFFER_WIDTH_MAX); //clear down buffer
        offset = 0;
        lineCount++;
        if( lineCount >= MAX_NO_LINES ) exit(EXIT_FAILURE);//safety net
        while ((character = getc(file)) != NEW_LINE && character != EOF) {
            buffer[offset] = character;
            offset++;
            if (offset >= BUFFER_WIDTH_MAX) {
                printf("Line too wide to fit into buffer!\n");
                exit(EXIT_FAILURE);
            }
        }
        //if (strncmp(buffer, stopString,7) == 0) break; //termination match found 1st 4 characters only
        if (strstr(buffer, stopString)) break;
        printf("%s\n",buffer); //print the line
    }
    return 1;
}

//fpos_t findStart(FILE *file, char* searchString, int lenSwitchName)
fpos_t findStart(FILE *file, char* searchString)
{//***search string needs to ignore switch name
    //char* check;
    char buffer[BUFFER_WIDTH_MAX];
    fpos_t filePosition = 0;
    int character, offset = 0, lineCount = 0;
    memset(buffer, 0, BUFFER_WIDTH_MAX); //clear down buffer
    rewind(file);
    //filePosition = 7;//this is a test
    //fsetpos(file, &filePosition);//this is a test
    while (1) {//look for the begining
        while ((character = getc(file)) != NEW_LINE && character != EOF) {
            buffer[offset] = character;
            offset++;
            if (offset >= BUFFER_WIDTH_MAX) {
                printf("Line too wide to fit into buffer!\n");
                exit(EXIT_FAILURE);
            }
        }
        //check = strstr(buffer, searchString);
        if (strstr(buffer, searchString)) break; //found substring in searchString
        if (strcmp(buffer, searchString) == 0) break; //match found
        memset(buffer, 0, BUFFER_WIDTH_MAX); //clear down buffer
        offset =0;
        lineCount++;
        if( lineCount >= MAX_NO_LINES || character == EOF ) return NOT_FOUND;
    }
    fgetpos(file, &filePosition);
    return filePosition;
}
int showInfo(FILE *file, struct ChassisInfo *chassisInfo, struct FileDetails fileDetails)
{
    
    printf("File Name: %s\n",fileDetails.nameOfFile);
    printf("Switch Name: %s\n",chassisInfo->switchName);
    printf("Lines in file: %i\n",fileDetails.noOfLinesInFile);
    
    return 0;
}
int showMACTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nMAC Address Table\n");
    check = showSection(file, MAC_TABLE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
        
    }
    return 1;
}

int showVLANTable(FILE *file,char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nVLAN Table\n");
    check = showSection(file, VLAN_TABLE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showIntStatusTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nInterface Status\n");
    check = showSection(file, INT_STATUS, CtrPrompt);
    if (check == NOT_FOUND)
    {
        //check for alternate show command
        check = showSection(file, INT_STATUSS, CtrPrompt);
    }
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showIntCountTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nInterface Counters\n");
    check = showSection(file, INT_COUNTERS, CtrPrompt);
    if (check == NOT_FOUND)
    {
        //check for alternate show command
        check = showSection(file, INT_COUNTERSS, CtrPrompt);
    }
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showRfTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nRadio Link\n");
    check = showSection(file, RF_LINK, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
   
}
int showSensorTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nSensors\n");
    check = showSection(file, SENSOR_TABLE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showVLANPvidTable(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nSensors\n");
    check = showSection(file, VLAN_PVID, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showFans(FILE *file, char* CtrPrompt)
{
    char buffer[BUFFER_WIDTH_MAX];
    int character, offset = 0, lineCount = 0;
    cls();
    printf("\nFans\n");
    //we only need to see the first 4 lines for sensors
    fpos_t filePosition = 0;
    filePosition = findStart(file, SENSOR_TABLE);
    if (filePosition <=0) return NOT_FOUND;//not found
    fsetpos(file, &filePosition);
    while (1) {//print until you reach the stop string
        memset(buffer, 0, BUFFER_WIDTH_MAX); //clear down buffer
        offset = 0;
        lineCount++;
        if( lineCount >= MAX_NO_LINES ) exit(EXIT_FAILURE);//safety net
        while ((character = getc(file)) != NEW_LINE && character != EOF) {
            buffer[offset] = character;
            offset++;
            if (offset >= BUFFER_WIDTH_MAX) {
                printf("Line too wide to fit into buffer!\n");
                exit(EXIT_FAILURE);
            }
        }
        if ( lineCount >= FAN_LINES) return 1;
        printf("%s\n",buffer); //print the line
    }
    return 1;
}

int showSystem(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nSystem Details\n");
    check = showSection(file, SYS_DETAILS, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showHTTPServer(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nHTTP Server\n");
    check = showSection(file, HTTP_SERVER, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showICFStatus(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nICF Server\n");
    check = showSection(file, ICF_STATUS, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showIPArp(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nARP Table\n");
    check = showSection(file, IP_ARP, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showIPInt(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nIP Interfaces\n");
    check = showSection(file, IP_INT, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showIPRoute(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nIP Route\n");
    check = showSection(file, IP_ROUTE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showOSPFNeigh(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nOSPF Neighbours\n");
    check = showSection(file, OSPF_NEIGH, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showOSPFRoute(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nOSPF Settings\n");
    check = showSection(file, ROUTER_OSPF, "end");
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showLIC(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nLicense\n");
    check = showSection(file, LIC, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showLICUse(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nLicense Usage\n");
    check = showSection(file, LIC_USE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showLLDPInfo(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nLLDP Info\n");
    check = showSection(file, LLDP_INFO, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showLLDPNei(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nLLDP Neighbours\n");
    check = showSection(file, LLDP_NEI, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showLogging(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nLogging\n");
    check = showSection(file, LOGGING, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showManagement(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nManagement\n");
    check = showSection(file, MANAGE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showManufacture(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nManufacture Details\n");
    check = showSection(file, MANUF, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showSyncE(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nSyncE - Network Clock\n");
    check = showSection(file, SYNCE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showProtection(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nProtection\n");
    check = showSection(file, PROT, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}
int showOSPFSettings(FILE *file, char* CtrPrompt)
{
    int check = 0;
    cls();
    printf("\nOSPF Route\n");
    check = showSection(file, OSPF_ROUTE, CtrPrompt);
    if (check == NOT_FOUND) {
        printf("No Entry Found!\n");
    }
    return 1;
}

