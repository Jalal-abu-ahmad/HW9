#include "string.h"
#include "field.h"
#include "port.h"
#include "ip.h"

	// construct the rule bassed on it's type and it's pattern 
	// pattern= src/dst-port/ip
    Field::Field(String pattern, field_type type){
    	this->pattern = pattern;
    	this->type = type;
    }

	//construct the rule as one of four types that deal with 
	//dst/src & ip/port.
	// if non of these four are compatable se it to generic type
    Field::Field(String pattern){
    	this->pattern = pattern;
    	if(pattern.equals("src-ip") || pattern.equals("dst-ip")){
    		this->type=IP;

    	} else if(pattern.equals("src-port") || pattern.equals("dst-port")){
    		this->type=PORT;

    	} else{
    		this->type=GENERIC;
    	}
    }
    //destructor
    Field::~Field(){
    }

    //return the type of the rule PORT/IP/GENERIC 
    field_type Field::get_type() const{
    	if(this->type==PORT){
    		return PORT;

    	}else if(this->type==IP){
    		return IP;

    	}
    	return GENERIC;
    }
    //call the compatable function of the child classes (IP/PORT) 
    //to set the rule values
    bool Field::set_value(String val){
    	if(this->type==PORT){
    		return ((Port*)this->set_value(val));

    	}else if(this->type==IP){
    		return ((Ip*)this->set_value(val));

    	}
    	return false;	
    }
    //call the compatable function of the child classes (IP/PORT) 
    //to check if given packet field matches the rule values (set by set_values)
    bool Field::match_value(String val) const{
    	if(this->type==PORT){
    		Port *port=(Port*)this;
    		return port->match_value(val);

    	} else if(this->type==IP){
    		Ip *ip=(Ip*)this;
    		return ip->match_value(val);

    	}
    	return false;
    }
    //calls match value with each one of the fields in the packet to check 
    //whether this field satisfies the rule 
    bool Field::match(String packet){
    	String *splited_packet_words;
 		size_t size;
 		bool value=false;
 		packet.split( ",= " , &splited_packet_words , &size );
 		//go through all packet fields until one matches this rule pattern
    	for(size_t i =0 ; i<size ; i++){
    		splited_packet_words[i]=splited_packet_words[i].trim();
    	    if(splited_packet_words[i].equals(this->pattern)){

    	    	value = match_value(splited_packet_words[i+1]);  
    	    }
    	}
    	delete[] splited_packet_words;
    	
    	return value;

    }