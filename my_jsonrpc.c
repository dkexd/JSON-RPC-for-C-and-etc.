#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"





#define	MAXSIZE 4096

static char buffer [MAXSIZE];

const char check_jsonrpc[]="\"2.0\"";

//FUNCTION DECLARATION
void jsonrpc_create(void);
void jsonrpc_read_test(char * text);
void jsonrpc_parse_reply(char data);
//JSON strings
char my_json_string[]="{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":    1920, \n\"height\":     1080, \n\"interlace\":  false,\n\"frame rate\": 24\n}\n}";
char sent[]="{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"POST\",\"params\":{\"url\":\"/network\",\"data\":{\":id\":\"bebb68a0-aaaa-11e6-86ca-001a65002cf0\",\":type\":\"urn:seluxit:xml:bastard:network-1.0\"}}}";
char pdata[]="{\"jsonrpc\":\"2.0\",\"id\": 1,\"result\":true}";


//DEFINITION Creating JSON RPC Request structure
void jsonrpc_create(){
  //char * jsonrpc_send_ver;
	//jsonrpc_send_ver = "2.0";


	cJSON *root,*params,*data,*number;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "jsonrpc", cJSON_CreateString("2.0"));
	cJSON_AddItemToObject(root, "id", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(root, "method", cJSON_CreateString("POST"));
	cJSON_AddItemToObject(root, "params", params = cJSON_CreateObject());
		cJSON_AddStringToObject(params, "url", "/network/bebb68a0-aaaa-11e6-86ca-001a65002cf0/device/bebb68a0-bbbb-11e6-86ca-001a65002cf0/service");
		cJSON_AddItemToObject(params, "data", data = cJSON_CreateObject());
			cJSON_AddStringToObject(data, ":id", "1c727866-c5bb-45e6-977e-7a3828a4b526");
			cJSON_AddStringToObject(data, ":type", "led");
			cJSON_AddStringToObject(data, "permission", "rw");
			cJSON_AddStringToObject(data, "type", "on/off");
			cJSON_AddItemToObject(data, "number", number = cJSON_CreateObject());
				cJSON_AddNumberToObject(number, "min", 0);
				cJSON_AddNumberToObject(number, "max", 1);
				cJSON_AddNumberToObject(number, "step", 1);
			cJSON_AddStringToObject(data, "status", "ok");

	char *new_json_string=cJSON_Print(root);
	printf("%s\n", new_json_string);
	//CALLING function to parse newly created JSONRPC string
	jsonrpc_read_test(new_json_string);



}
//DEFENITION Parsing created JSON RPC Request to send string
void jsonrpc_read_test(char * new_json_string){

		cJSON * root = cJSON_Parse(new_json_string);
		cJSON * params = cJSON_GetObjectItem(root,"params");
		cJSON * data = cJSON_GetObjectItem(params,"data");
		cJSON * number = cJSON_GetObjectItem(data,"number");
	//	cJSON * max = cJSON_GetObjectItem(number,"max");
		int maxmax = cJSON_GetObjectItem(number,"max")->valueint;
		//printing out value of max variable insude the JSONRPC structure
		printf("root/params/data/number/max = %d\n",maxmax);
}
//DEFENITION Parsing recieved JSON RPC Response
void jsonrpc_parse_reply(char data) {


		printf("%s\n",pdata);
		cJSON * root = cJSON_Parse(pdata);
		cJSON * jsonrpc = cJSON_GetObjectItem(root,"jsonrpc");
		char * jsonrpc_recieve_ver = cJSON_Print(jsonrpc);
		cJSON * id = cJSON_GetObjectItem(root,"id");
		int jsonrpc_recieve_id = cJSON_GetObjectItem(root,"id")->valueint;
		char * jsonrpc_recieve_id_txt = cJSON_Print(id);
		cJSON * result = cJSON_GetObjectItem(root,"result");
		char * jsonrpc_recieve_result = cJSON_Print(result);

		cJSON_Delete(root);

		printf("RECIEVED JSON RPC MESSAGE!\n");
		printf("--------------------------\n");
		printf("JSON RPC version: %s\n",jsonrpc_recieve_ver);
		printf("JSON RPC id: %d\n",jsonrpc_recieve_id);
		printf("JSON RPC id as string: %s\n",jsonrpc_recieve_id_txt);
		printf("JSON RPC result: %s\n",jsonrpc_recieve_result);
		printf("--------------------------\n");
}




/*---------------------------------------------------------------------------------------------------*/


int main(void) {

	//Parsing recieved JSON RPC Response object, reading all it's values and printing them out
  jsonrpc_parse_reply(*pdata);
  //CALLING function to create JSON RPC Request objects's structure, putting into string, print it and then parse it til value of a key :"max" and print that value
	jsonrpc_create();


}





/* ------------------------------------------------------------------------------------------------------
typedef struct {
    char jsrpc_ver;
    char method;
		char params;
		char id;
} jsonrpc;

jsonrpc one;

------------------------------------------------------------

// Parse text to JSON, then render back to text, and print!

void doit(char *text)
{
	char *out;
	cJSON *json;

	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);

		free(out);
	}
}



------------------------------------

printf("%s\n",my_json_string);
cJSON * root = cJSON_Parse(my_json_string);
cJSON * format = cJSON_GetObjectItem(root,"format");
int framerate = cJSON_GetObjectItem(format,"frame rate")->valueint;
cJSON *frame_rate_data = cJSON_GetObjectItem(format,"frame rate");
cJSON_GetObjectItem(format,"frame rate")->valuedouble = 25;
char * rendered = cJSON_Print(format);
cJSON_Delete(root);
printf("%s\n",rendered);

--------------- Print JSON RPC version --------------------------

printf("%s\n",recieved);

cJSON * root = cJSON_Parse(recieved);
cJSON * jsonrpc = cJSON_GetObjectItem(root,"jsonrpc");
char * jsonrpc_ver = cJSON_Print(jsonrpc);
cJSON_Delete(jsonrpc);
printf("%s\n",jsonrpc_ver);

------------- Compare if JSON RPC version is 2.0--------------------------


printf("%s\n",recieved);

cJSON * root = cJSON_Parse(recieved);
cJSON * jsonrpc = cJSON_GetObjectItem(root,"jsonrpc");
char * jsonrpc_ver = cJSON_Print(jsonrpc);
if (strcmp(jsonrpc_ver, check_jsonrpc) == 0) {
	printf("OK!\n");
	cJSON_Delete(jsonrpc);
	printf("%s\n",check_jsonrpc);
	printf("%s\n",jsonrpc_ver);
}
else {
	printf("NOT OK!\n");
	cJSON_Delete(jsonrpc);
}
}
*/
