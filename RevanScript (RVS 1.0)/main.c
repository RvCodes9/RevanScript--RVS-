/*

Copyright © Rəvan Babayev All rights reserved.

RevanScript (RVS) Programming language
RevanScript interpreter C source codes

*/


#include <stdio.h> // Standart input/output kitabxanasıdır (printf, fgets, puts, putchar) kimi funksiyalar üçün lazımdır.
#include <stdlib.h> // Standart Library kitabxanasıdır (malloc, calloc, realloc, free, system) kimi yaddaş ı dinamik idarə edə bilmək üçün lazım olan funksiyalar var.
#include <stdbool.h> // Standart Boolean kitabxanasıdır (true, false) daha rahat (1, 0) anlamını oxunaqlı hala gətirmək üçündür.
#include <stddef.h> // Standart Define kitabxanasıdır (size_t) kimi içində bəzi məlumat tipləri var.
#include <string.h> // String algorithms / alqoritimləri var.
#include <stdint.h> // Standart Integer kitabxanasıdır (int8_t, int16_t, int32_t, int64_t) kimi məlumat tipləri var.



#define VARIABLE_NAME_MAX_COUNT 100 // Dəyişənin maksimum sayı
#define VARIABLE_DATA_MAX_COUNT 100 // Dəyişəndəki məlumatın sayı
#define VARIABLE_NAME_MAX_LENGHT 100 // Dəyişən adının uzunluğu
#define VARIABLE_DATA_MAX_LENGHT 100 // Dəyişəndəki məlumatın uzunluğu



bool ARG_CONTROL(int argc, char** argv){

    if (argc == 2){
        
        size_t arglen = strlen(argv[1]);

        char example[4] = ".rvs";
        int8_t example_counter = 0;
            
        for (int i = (arglen - 4); i < arglen; i++){
            if (example[example_counter++] != argv[1][i]) return false;
        }

        return true;
    }  
    
    else{
        return false;
    }
}



static char variables_name_list[VARIABLE_NAME_MAX_COUNT][VARIABLE_NAME_MAX_LENGHT];
static char variables_data_list[VARIABLE_DATA_MAX_COUNT][VARIABLE_DATA_MAX_LENGHT];

static int variables_list_counter = 0;



bool VAR_KEYWORD(char* code){
	
	if (code[0] == 'v' && code[1] == 'a' && code[2] == 'r' && code[3] == ' '){
		
		int i = 4;
		
		int n_counter = 0;
		int d_counter = 0;
		
		bool equal_active = false;
        bool string_literal_active = false;
		
		while (true){
			
			if ((string_literal_active == false) && (code[i] == ';')){
				break;
			}
			
			else if ((string_literal_active == false) && (code[i] == ' ')){
				i++;
				continue;
			}
			
			else if (code[i] == '='){
				i++;
				equal_active = true;
				continue;
			}

            else if (equal_active == true && code[i] == '"'){

                if (string_literal_active == false){
                    string_literal_active = true;
                }

                else{
                    string_literal_active = false;
                }
            }
			
			else{
				
				if (equal_active != true){
					variables_name_list[variables_list_counter][n_counter++] = code[i];
				}
				
				else{
                    
                    if (string_literal_active == true){
                        variables_data_list[variables_list_counter][d_counter++] = code[i];
                    }
				}
			}
			
			i++;
		}
		
		// Əgər dəyişənə dəyər verilməyibsə avtomatik NULL dəyəri alır
		if (equal_active == false){
			char null_data[5] = "NULL";
			for (int j = 0; j < strlen(null_data); j++){
				variables_data_list[variables_list_counter][d_counter++] = null_data[j];
			}
		}
		
        // Sonuna NULL TERMINATOR CHARACTER qoyulur (\0)
		variables_name_list[variables_list_counter][n_counter] = '\0';
		variables_data_list[variables_list_counter][d_counter] = '\0';

		variables_list_counter++;

        return true;
	}
    
    else{
        return false;
    }
}


bool OUT_KEYWORD(char* code){

    if (code[0] == 'o' && code[1] == 'u' && code[2] == 't' && code[3] == ' '){
        
        // Variable Name Write Buffer

        int counter = 4;

        char variable_name_buffer[100];
        int variable_name_buffer_counter = 0;

        while (true){
        	
        	if (code[counter] == ';'){
        		break;
			}
			
			else if (code[counter] == ' '){
				counter++;
				continue;
            }
            
            else{
                variable_name_buffer[variable_name_buffer_counter++] = code[counter++];
            }
        }

        variable_name_buffer[variable_name_buffer_counter] = '\0';

        // Variable Data Print System

        for (int i = 0; i < variables_list_counter; i++){

            int variable_name_control_count = 0;

            for (int j = 0; variable_name_buffer[j] != '\0'; j++){
                if (variable_name_buffer[j] == variables_name_list[i][j]){
                    variable_name_control_count++;
                }
            }

            if (strlen(variable_name_buffer) == variable_name_control_count){
                
                for (int j = 0; variables_data_list[i][j] != '\0'; j++){

                    if (variables_data_list[i][j] == '%'){
                        putchar('\n');
                    }

                    else if (variables_data_list[i][j] == '#'){
                        putchar('\t');
                    }

                    else{
                        putchar(variables_data_list[i][j]);
                    }
                }

                break;
            }
        }

        return true;
    }

    else{
        return false;
    }
}



bool INP_KEYWORD(char* code){

    if (code[0] == 'i' && code[1] == 'n' && code[2] == 'p' && code[3] == ' '){

        char variable_name_buffer[100];
        short variable_name_buffer_counter = 0;

        int variable_name_counter = 4;

        while (code[variable_name_counter] != ';'){

            if (code[variable_name_counter] == ' '){
                variable_name_counter++;
                continue;
            }

            else{
                variable_name_buffer[variable_name_buffer_counter++] = code[variable_name_counter];
            }

            variable_name_counter++;
        }

        variable_name_buffer[variable_name_buffer_counter] = '\0';



        char* variable_data_pointer = NULL;

        for (int i = 0; i < variables_list_counter; i++){

            int control_count = 0;

            for (int j = 0; variable_name_buffer[j] != '\0'; j++){

                if (variable_name_buffer[j] == variables_name_list[i][j]){
                    control_count++;
                }

            }

            if (control_count == strlen(variables_name_list[i])){
                variable_data_pointer = variables_data_list[i];
                break;
            }

        }


        if (variable_data_pointer != NULL){
            variable_data_pointer[0] = '\0';
            fgets(variable_data_pointer, 99, stdin);
        }

        return true;
    }

    else{
        return false;
    }
}


bool PRT_KEYWORD(char* code){

    if (code[0] == 'p' && code[1] == 'r' && code[2] == 't' && code[3] == ' '){

        int code_counter = 4;

        bool string_literal_active = false;

        while (true){

            if (code[code_counter] == '"'){

                if (string_literal_active == false){
                    string_literal_active = true;
                }

                else{
                    string_literal_active = false;
                }
            }

            else if (string_literal_active == true){
                
                if (code[code_counter] == '%'){
                    putchar('\n');
                }

                else if (code[code_counter] == '#'){
                    putchar('\t');
                }

                else{
                    putchar(code[code_counter]);
                }
            }

            else if (string_literal_active == false && code[code_counter] == ';'){
                break;
            }

            code_counter++;

        }

        return true;
    }

    else{
        return false;
    }
}


static bool cli_pause_mode = true;


bool END_KEYWORD(char* code){

    if (code[0] == 'e' && code[1] == 'n' && code[2] == 'd' && code[3] == ';'){
        cli_pause_mode = false;
        return true;
    }

    else{
        return false;
    }
}



bool ENDLINE_CONTROL(char* code){

    bool string_literal_active = false;

    for (int i = 0; code[i] != '\0' && code[i] != '\n'; i++){  //  i < strlen(code)

        if (code[i] == '"'){

            if (string_literal_active == false)
                string_literal_active = true;

            else
                string_literal_active = false;
        }

        else if (string_literal_active == false)
            if (code[i] == ';') return true;
    }

    return false;
}



bool RUNTIME(FILE* ScriptFile){
    
    // Əsas Runtime loop/Dövr
    while (!feof(ScriptFile)){
    	
        // kodu yaddaşda saxlamaq üçün code dəyişəni 2049 bayt ayırıram son bir bayt \0 (NULL TERMİNATOR CHARACTER) üçün
    	char* code = (char*) calloc(2049, 1);
    	
        // NULL deyilsə yaddaş ayırma uğurlu keçib anlamına gəlir
    	if (code != NULL){
            
            // Fayldan kodu oxuyub code dəyişəninə yazıram maksimum 2 KB oyuyuram 
	        fgets(code, 2048, ScriptFile);
	        
            // Sətir heç bir kod yoxsa
	        if (code[0] == '\0' || code[0] == '\n') continue;
            
            // Əgər sətirdə sonlandırıcı yoxsa proqram dayandırılır false dönər.
            if (ENDLINE_CONTROL(code) == false) return false;

            // Keywords RevanScript Control System
	         
            // out açar sözünün işləndiyini yoxlayan funksiya
	        if (OUT_KEYWORD(code) == true){
                free(code);
                continue;
            }
	        
	        // var açar sözü dəyishen yaratmaq üçündür
	        else if (VAR_KEYWORD(code) == true){
                free(code);
                continue;
            }
            
            // inp açar sözü dəyişənə klaviyaturadan alınan mətni yazır
            else if (INP_KEYWORD(code) == true){
                free(code);
                continue;
            }

            else if (PRT_KEYWORD(code) == true){
                free(code);
                continue;
            }

            // end açar sözü pause modunu deaktiv edir.
            else if (END_KEYWORD(code) == true){
                free(code);
                continue;
            }

            else{
                // kodun olduğu yaddaşı azad edirik
	            free(code);
            }
	    } 
        
        // NULL dırsa uğursuz yaddaş ayırması baş verib 
        else return false;
    }
     
    // Ekranın proqram bitən kimi bağlanmasını əngəlləyir.
    if (cli_pause_mode == true){
        printf("\n");
        system("pause");
    }
    
    // Bütün proseslər uğurlu olubsa onda TRUE döndəririk
    return true;
}



bool INTERPRETER(char* script_name){

    FILE* ScriptFile;
    ScriptFile = fopen(script_name, "r");

    if (ScriptFile != NULL){
        if (RUNTIME(ScriptFile) == false) return false;
    } 
    
    else return false;
}



int main(int argc, char** argv){
    
    // .rvs file type control reader.
    if (ARG_CONTROL(argc, argv) == false) return 1;
    
    // Interpreter 
    if (INTERPRETER(argv[1]) == false) return 1;
    
    // Problem yoxsa
    return 0;
}
