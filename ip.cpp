#include "ip.h"    
#include "field.h"

#define MASK_SEGMENT 2
#define SEGMENTS 4

    //constructor
    Ip::Ip(String pattern): Field(pattern){
    	this->low  = 0;
    	this->high = 0;
    	}
    // this function sets the values of the rule in accordance with the string
    // that it recieves (val)
    bool Ip::set_value(String val){
    	unsigned int ip=0;
    	unsigned int mask,mask_num;
        String *splited_ip_words;
    	bool value=true;
 		size_t size;
    	val.split( "/." , &splited_ip_words , &size );
        //check if the rule contains 5 fields after splitting- 4->ip +1->mask
    	if(size!=5){
    		value=false;
    	}
    	for(size_t i=0;i<size;i++){
    		splited_ip_words[i]=splited_ip_words[i].trim();
    	}
        // make sure the rule is of the correct form and number range
        for(size_t i=0 ; i<SEGMENTS ;i++){
        	if(!(splited_ip_words[i].to_integer()>=0 
        		&& splited_ip_words[0].to_integer()<=255)){
        		value=false;
            //calculate IP
        	} else {
        		ip=ip | ((splited_ip_words[i].to_integer())<<(8*(3-i)));
        	}
        }

        //check if the mask has the correct range
        if(!(splited_ip_words[SEGMENTS].to_integer()>=0
        	 && splited_ip_words[SEGMENTS].to_integer()<=32)){
        	value=false;
        } else {
        	mask_num= splited_ip_words[SEGMENTS].to_integer();
        }

        //calculate the IP (subnet) mask
        if(value){
        	if(mask_num==32){
    			mask=0xffffffff;
    		} else if(mask_num==0){
                mask=0;
            } else {
    			mask=(1<<(32-mask_num))-1;
    			mask=~mask;
    		}
            //set the lowest and highest IP that are possible in specific subnet 
            // in accordance with the IP and mask-bit numbers
    		this->low= ip & mask;
    		this->high=  ~mask | this->low;

        }
        delete[] splited_ip_words;
    	return value;
    }
    // check wether the string val which contains an IP is in the range 
    //[low:high] set by the rule
    bool Ip::match_value(String val) const{ 
        String *splited_ip_words;
 		size_t size;
        unsigned int ip=0;

        val=val.trim();
    	val.split( "=-./" , &splited_ip_words , &size );
    	for(size_t i=0;i<size;i++){
    		splited_ip_words[i]=splited_ip_words[i].trim();
    	}
    	
        //calculate IP address
    	for(int i=0;i<SEGMENTS;i++){
    		ip=ip | splited_ip_words[i].to_integer()<<(8*(3-i));
    	}

    	delete[] splited_ip_words;
 
    	if((this->low <= ip) && (ip<=this->high)){
    		return true;
    	}
    	return false;
    }

