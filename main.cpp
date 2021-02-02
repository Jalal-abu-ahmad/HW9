#include "string.h"
#include "field.h"
#include "port.h"
#include "ip.h"
#include "input.h"

// this function takes a rule as a string and checks if a list of packets 
//in a file satisfy this rule or not
int main (int argc, char **argv) {
	//check if the rule has a correct format
	if (check_args(argc,argv)){
		return 1;
	}
		String str = String(argv[1]);
		String *splitted_rule = nullptr;
		size_t size;

		str=str.trim();
		str.split("=",&splitted_rule,&size);

		for(size_t i=0;i<size;i++){
			splitted_rule[i]=splitted_rule[i].trim();
		}

		if(splitted_rule[0].equals("src-ip") 
		                                 || splitted_rule[0].equals("dst-ip")) {

			Ip ip_rule =  Ip(splitted_rule[0]);
			ip_rule.set_value(splitted_rule[1]);
			parse_input(ip_rule);

		} else if((splitted_rule[0].equals("src-port"))
			                 	     || (splitted_rule[0].equals("dst-port"))) {

			Port port_rule = Port(splitted_rule[0]);
			port_rule.set_value(splitted_rule[1]);
			parse_input(port_rule);

		}
		
	delete[] splitted_rule;
	return 0;
}