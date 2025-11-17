/*

RevanScript (RVS) Programming language
RevanScript interpreter C source codes

*/


#include <stdio.h> // Standart input/output kitabxanasıdır (printf, fgets, putchar) kimi funksiyalar üçün lazımdır.
#include <stdlib.h> // Standart Library kitabxanasıdır (malloc, calloc, realloc, free, system) kimi yaddaş ı dinamik idarə edə bilmək üçün lazım olan funksiyalar var.
#include <stdbool.h> // Standart Boolean kitabxanasıdır (true, false) daha rahat (1, 0) anlamını oxunaqlı hala gətirmək üçündür.
#include <stddef.h> // Standart Define kitabxanasıdır (size_t) kimi içində bəzi məlumat tipləri var.
#include <string.h> // String algorithms / alqoritimləri var.



bool ARG_CONTROL(int argc, char** argv){

    if (argc == 2){
        
        size_t arglen = strlen(argv[1]);

        char example[4] = ".rvs";
        short example_count = 0;
            
        for (int i = (arglen - 4); i < arglen; i++){
            if (example[example_count++] != argv[1][i]) return false;
        }

        return true;
    }  
    
    else return false;
}



static char variables_name_list[100][100];
static char variables_data_list[100][100];

static int variables_list_counter = 0;



void VAR_KEYWORD(char* code){
	
	if (code[0] == 'v' && code[1] == 'a' && code[2] == 'r'){
		
		int i = 3;
		
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
	}
}


void OUT_KEYWORD(char* code){

    if (code[0] == 'o' && code[1] == 'u' && code[2] == 't'){

        // String literal

        bool string_literal_active = false;
        int count = 3;
        
        bool variable_call_active = false;
        char variable_name_buffer[100];
        int variable_name_buffer_counter = 0;
        
        while (true){
        	
        	if ((string_literal_active == false) && (code[count] == ';')){
        		break;
			}
			
			else if ((string_literal_active == false) && (code[count] == ' ')){
				count++;
				continue;
			}
        	
            else if (code[count] == '"'){

                if (string_literal_active == true) 
                    string_literal_active = false;
                
                else {
                    string_literal_active = true;
                }
            }
            
            else if (string_literal_active == true){
                if (code[count] == '%') putchar('\n');
                else if (code[count] == '#') putchar('\t');
                else putchar(code[count]);
            }
            
            else{

                if (variable_call_active == false){
                    variable_call_active = true;
                }

                variable_name_buffer[variable_name_buffer_counter++] = code[count];
            }
            
            count++;
        }

        if (variable_call_active == true){

            variable_name_buffer[variable_name_buffer_counter] = '\0';

            int i = 0;

            for (i ; i < variables_list_counter; i++){

                int variable_name_control_count = 0;

                for (int j = 0; variables_name_list[i][j] != '\0'; j++){
                    if (variable_name_buffer[j] == variables_name_list[i][j]){
                        variable_name_control_count++;
                    }
                }

                if (strlen(variable_name_buffer) == strlen(variables_name_list[i])){
                    break;
                }
            }
            
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
        }
    }
}



void INP_KEYWORD(char* code){

    if (code[0] == 'i' && code[1] == 'n' && code[2] == 'p'){

        char variable_name_buffer[100];
        short variable_name_buffer_counter = 0;

        int variable_name_counter = 3;

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
    }
}



static bool cli_pause_mode = true;



void END_KEYWORD(char* code){
    if (code[0] == 'e' && code[1] == 'n' && code[2] == 'd'){
        cli_pause_mode = false;
    }
}


bool ENDLINE_CONTROL(char* code){

    bool string_literal_active = false;

    for (int i = 0; i < strlen(code); i++){

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
	         
            // out açar sözünün işləndiyini yoxlayan funksiya
	        OUT_KEYWORD(code);
	        
	        // var açar sözü dəyishen yaratmaq üçündür
	        VAR_KEYWORD(code);
            
            // inp açar sözü dəyişənə klaviyaturadan alınan mətni yazır
            INP_KEYWORD(code);

            // end açar sözü pause modunu deaktiv edir.
            END_KEYWORD(code);
	        
            // kodun olduğu yaddaşı azad edirik
	        free(code);
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
