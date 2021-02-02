#include "port.h"
#include "string.h"
#include "field.h"


    Port::Port(String pattern): Field(pattern) {
    	this->range[0] = 0;
    	this->range[1] = 0;

    }

    // this function sets the values of the rule in accordance with the string
    // that it recieves (val)
    bool Port::set_value(String val){ 
    	String *splited_port_words;
 		size_t size;
    	val.split( "-" , &splited_port_words , &size );
    	for(size_t i=0;i<size;i++){
    		splited_port_words[i]=splited_port_words[i].trim();
    	}
    	// make sure the rule is of the correct format:
    	//has two fields and the numbers are of the correct range
    	if(size == 2 
        && ( (0<=splited_port_words[0].to_integer()) 
        && ((splited_port_words[0].to_integer())<=65535))
        && ((0<=splited_port_words[1].to_integer()) 
        && (splited_port_words[1].to_integer())<=65535)
        && (splited_port_words[0].to_integer())<=
        								(splited_port_words[1].to_integer())) {
    		//set the rule port range
           	this->range[0] = (splited_port_words[0].to_integer());
    		this->range[1] = (splited_port_words[1].to_integer());
    		delete[] splited_port_words;
    		return true;
        }
    	delete[] splited_port_words;
        return false;

    }
    // check wether the string val which contains a port is in the range 
    // set by the rule
    bool Port::match_value(String val) const{
    	val=val.trim();
    	if((val.to_integer()>=this->range[0])&&(val.to_integer()<=this->range[1])){
    		return true;
    	}
       	return false;

    }