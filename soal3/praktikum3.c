#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <wait.h>

int main() 
{ 
    pid_t child;
    int stat;

    child = fork(); 
      
    if (child < 0) 
	  {
		    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
	  }

    if (child == 0) // INI PROSES PERTAMA
	  { 
		    char *argv[] = {"mkdir", "-p", "/home/kholilah/modul2/indomie", NULL};
		    execv("/bin/mkdir", argv);
	  } 
  
    else 
    {      
		   while ((wait(&stat)) > 0);
          child = fork(); // INI PROSES KEDUA
        	if (child == 0) 
			    { 
			    	  sleep(5);
				      char *argv[] = {"mkdir", "-p", "/home/kholilah/modul2/sedaap", NULL};
			    	  execv("/bin/mkdir", argv);
        	} 
        	else 
			    {               
				      while ((wait(&stat)) > 0);
	        		    child = fork(); // INI PROSES KETIGA
                	if (child == 0) 
					        {
						          char *argv[] = {"unzip", "/home/kholilah/Downloads/jpg.zip", "-d", "/home/kholilah/modul2", NULL};
						          execv("/usr/bin/unzip", argv);
            		  }
            		  else 
					        {        
						          while ((wait(&stat)) > 0);
                			    child = fork(); // INI PROSES KEEMPAT
							            if (child == 0)
							            {
								              char *argv[] = {"find", "/home/kholilah/modul2/jpg/", "-maxdepth", "1", "-mindepth", "1", "-type", "d", "-exec", "/bin/mv", "-t", "/home/kholilah/modul2/indomie", "{}",";", NULL};
								              execv("/usr/bin/find", argv);
							            }
							            else 
							            { 
								              while ((wait(&stat)) > 0);
                					        child = fork(); // INI PROSES KELIMA
									                if (child == 0)
									                {
										                  char *argv[] = {"find", "/home/kholilah/modul2/jpg/", "-maxdepth", "1", "-mindepth", "1", "-type", "f", "-exec", "/bin/mv", "-t", "/home/kholilah/modul2/sedaap", "{}",";", NULL};
										                  execv("/usr/bin/find", argv);
									                }
									                else
									                {
										                  while ((wait(&stat)) > 0);
                							            child = fork(); // INI PROSES KEENAM
											                    if (child == 0)
											                    {
												                      char *argv[] = {"find", "/home/kholilah/modul2/indomie/", "-maxdepth", "1", "-mindepth", "1", "-type", "d", "-exec", "/usr/bin/touch", "{}/coba1.txt", "'\'", ";", NULL};
												                      execv("/usr/bin/find", argv);
											                    }
											                    else
											                    {
												                      while((wait(&stat)) > 0);
													                    sleep(3);
													                    char *argv[] = {"find", "/home/kholilah/modul2/indomie/", "-maxdepth", "1", "-mindepth", "1", "-type", "d", "-exec", "/usr/bin/touch", "{}/coba2.txt", "'\'", ";", NULL};
													                    execv("/usr/bin/find", argv);
											                    }	
									                }
							            }         
					        }         
		      }	       
    } 
}

