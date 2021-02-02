#include "string.h"
#include <stddef.h>
#include <iostream>

    /**
     * @brief Initiates an empty string
     */
    String::String(){
        data = new char[1];
        *data='\0';
        this->length = 1;
    }

    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str){
        this->length = str.length;
        this->data = new char[this->length];
        for(size_t i=0;i<this->length;i++){
            data[i] = str.data[i];
        }

    }

    /**
     * @brief Initiates a string from char array
     */
    String::String(const char *str){
        this->length = 0;
        while(str[this->length]!='\0') { 
            this->length++;
        }
        this->length++;
        this->data=new char[this->length];
        for(size_t i=0;i<this->length;i++){
            data[i] = str[i];
        }
    }

    // destructor
    String::~String(){
        if(this){
        delete[] this->data;
        }
    }

    /**
     * @brief Changes this from String
     */
    String& String::operator=(const String &rhs){
        delete[] this->data;
        this->data= new char[rhs.length];
        for(size_t i=0;i<rhs.length;i++){
          this->data[i] = rhs.data[i];  
        }
        this->length=rhs.length;
        return *this;
    }

    /**
     * @brief Changes this from char array
     */
    String& String::operator=(const char *str){
        delete[] this->data;
        this->length = 0;
        while(str[this->length]!='\0'){
            this->length++;
        } 
        this->length++;

        this->data = new char[this->length];
        for(size_t i=0;i<this->length;i++){
            this->data[i] = str[i];
        }
        return *this;

    }
    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const{
        for(size_t i=0;i<rhs.length;i++){
            if(this->data[i] != rhs.data[i]){
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
            for(size_t i=0;i<this->length;i++){
            if(this->data[i] != rhs[i]){
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String::split(const char *delimiters, String **output, size_t *size) const{
        *size = 0;
        char *str_tmp= new char[this->length];
        int current_str_len = 0,done=0;
        int *delimiters_check= new int[this->length];
        String *splitted= new String[this->length];      

        // define an array with the same length as the original string and put 
        //ones where there is a delimiter and zero where there isn't
        for(size_t i = 0 ; i<this->length ; i++){
            delimiters_check[i] = 0;
            for(size_t j = 0 ; delimiters[j] !='\0' ; j++){
                if (this->data[i] == delimiters[j]){
                    delimiters_check[i] = 1;
                }
            }
        }
        size_t i =0;
        for(i=0;i<=this->length;i++){
            //this while makes a new string and places it in the appropriate 
            //place in output, increments size and resets the parameters of 
            //current string to continue splitting THIS 
            while ((delimiters_check[i] && i<this->length)||done){
                if(current_str_len){
                    str_tmp[current_str_len] ='\0';
                    String str= String(str_tmp);
                    splitted[*size] = str;
                    delete[] str_tmp;
                    str_tmp= new char[this->length];
                    current_str_len=0;
                    (*size)++;
                    if(done){
                        done=0;
                        i=this->length+1;
                    }
                }
                i<this->length ? i++ :i;
            }
            // this while loads the string between two delimiters into a 
            //temporary string
            while ( !(delimiters_check[i]) && i<this->length){
                str_tmp[current_str_len] = (this->data)[i];
                current_str_len++;
                i<this->length ? i++ :i;
                if(i==(this->length)){
                    done=1;
                }
            }
            i--;
        }

        delete[] str_tmp;
        //if output is not NULL load the splitted strings into output
        if(output){
        *output = splitted;
        } else {
        delete[] splitted;
    }
    delete[] delimiters_check;
}

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{
        int sum = 0;
        size_t i=0;
        while(this->data[i]){
            if(this->data[i] >= '0' && this->data[i] <='9'){
                sum = 10 * sum + (this->data[i] - '0'); 
            } else {
                return 0;
            }
            i++;
        }
        return sum;
    }

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{
        char *str_tmp= new char[this->length];
        int start_spaces = 0;
        int end_spaces = this->length-2;
        while(this->data[start_spaces] == ' ') {
            start_spaces++; 
        }
        while(this->data[end_spaces] == ' ') {
            end_spaces--;
        }
        for (int i=start_spaces; i<=end_spaces; i++){
            str_tmp[i-start_spaces] = this->data[i];
        }
        str_tmp[end_spaces+1]='\0';
        String str = String(str_tmp);
        delete[] str_tmp;
        return str;
    }