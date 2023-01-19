#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   FILE *fileptr;
   char *buffer;
   long filelen;
   char label[256];
   char holder[256];
   char format[][256] = {"m_id","m_Label", "m_TypeID", "m_DisplayLevel", "m_BreakRate", "m_MaxSLD", "m_MaxHP", "m_MaxSP", "m_AtkP", "m_DefP", "m_AtkM", "m_DefM", "m_Agi", "m_Crt", "m_CrtDef", "m_EquipAtk", "m_ResistAilmentID", "m_ResistAilment", "m_TacticalAssignID", "m_SkillsID", "m_Exp", "m_Money", "m_DropReward", "m_EventDropRewards", "m_StatusOffset", "m_Bottle", "m_Name", "m_Level", "m_Hp", "m_Shield","m_RaceIndices","m_DisplaySpecialSkillGauge","m_GenerateSpecialSkillValueOrverTurn","m_ReduceSpecialSkillValueBreak","m_MaxSpecialSkillValue"};
   char tmplabel[256];

   int format_pointer = 0;
   int matches = 1;
   int parse_pointer_start = 0;
   int parse_pointer_end = 0;
   // intent: pring label: holder

   fileptr = fopen("EnemyID.uexp", "rb");  // Open the file in binary mode
   fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
   filelen = ftell(fileptr);             // Get the current byte offset in the file
   rewind(fileptr);                      // Jump back to the beginning of the file

   buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
   fread(buffer, filelen, 1, fileptr); // Read in the entire file
   fclose(fileptr); // Close the file


   printf("m_id,m_Label,m_TypeID,m_DisplayLevel,m_BreakRate,m_MaxSLD,m_MaxHP,m_MaxSP,m_AtkP,m_DefP,m_AtkM,m_DefM,m_Agi,m_Crt,m_CrtDef,m_EquipAtk,m_ResistAilmentID,m_ResistAilment,m_TacticalAssignID,m_SkillsID,m_Exp,m_Money,m_DropReward,m_EventDropRewards,m_StatusOffset,m_Bottle,m_Name,m_Level,m_Hp,m_Shield,m_RaceIndices,m_DisplaySpecialSkillGauge,m_GenerateSpecialSkillValueOrverTurn,m_ReduceSpecialSkillValueBreak,m_MaxSpecialSkillValue");
   for (int i = 0; i < filelen; i++){
      strncpy(label, buffer + i, strlen(format[format_pointer]));
      label[strlen(format[format_pointer])] = '\0';
      matches = strcmp(label, format[format_pointer]);


      if (matches == 0) {
         parse_pointer_end = i; // end secured.
         strncpy(tmplabel, buffer+parse_pointer_start, parse_pointer_end-parse_pointer_start);
         // printf("Start: %d, End: %d\n",parse_pointer_start,parse_pointer_end);
         for (int y = parse_pointer_start; y < parse_pointer_end && y!=0; y+=1)
         {
            printf("%02x", (unsigned int)(buffer[y] & 0xff));
            // I fucking hate this so much for some reason it reads anything like 0xf? as 0xfffff? so I have to do this
         }
         if (format_pointer!=0){
            printf(",");
         } else {
            printf("\n");
         }
         parse_pointer_start = i+strlen(format[format_pointer]); // start secured.
         // printf("**%s**", label);
         if (format_pointer < 34){
            format_pointer++;
         } else {
            format_pointer=0;
         }
      }
   }
   parse_pointer_end = filelen;
   for (int y = parse_pointer_start; y < parse_pointer_end; y+=1)
   {
      printf("%02x", (unsigned int)(buffer[y] & 0xff)); 
   }

   printf("\n");

   return 0;
}
