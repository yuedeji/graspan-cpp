#include "context.h"

Context::Context(int argc, char** argv) {
	//if user don't typing input value
	cout << "argc ==" << argc << endl;
	if(argc==1){
		//50MB
		//parameters.insert(std::make_pair(MEM_BUDGET_KEY, 7730941133));
		memBudget = (unsigned long long int) 7730941133; // 1073741824
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, 10));
		//src, numEdge = 8bytes dst, label = 5bytes
		//worst case is use 13bytes per edges
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, parameters[MEM_BUDGET_KEY] / 13));
		cout << "Max_Edges_Partition =" << (parameters[MEM_BUDGET_KEY]) / 13 << endl;
		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	} else{
		char *p_token = NULL;
		char *context = NULL;

		for(int i=0;i<argc;i++){
			p_token = strtok_r(argv[i], "=", &context);
		/*	if(i<2){
				if (i == 0) {
					parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, parameters[compare[i]] / 13));
					cout << "Max_Edges_Partition =" << (parameters[MEM_BUDGET_KEY]) / 13 << endl;
					continue;
				}
				parameters.insert(std::make_pair(compare[i], (unsigned long long int)atoi(context)*(unsigned long long int)1073741824));
				memBudget = (unsigned long long int)atoi(context)*(unsigned long long int)1073741824;
				cout << "test" << endl;
				
			} else{
				if((bool)context){
					flags.insert(std::make_pair(compare[i],true));
				} else{
					flags.insert(std::make_pair(compare[i],false));
				}
			}*/
			if (!strncmp(argv[i], INPUT_GRAPH_FILE_KEY.c_str(), sizeof(argv[i]))) {
				filePath.insert(std::make_pair(INPUT_GRAPH_FILE_KEY, context));
				cout << "INPUT_GRAPH_FILE_KEY =" << context << endl;
				//error
			}
			else if (!strncmp(argv[i], GRAMMAR_FILE_KEY.c_str(), sizeof(argv[i]))) {
				filePath.insert(std::make_pair(GRAMMAR_FILE_KEY, context));
				cout << "GRAMMAR_FILE_KEY =" << context << endl;
			}
			else if (!strncmp(argv[i], MEM_BUDGET_KEY.c_str(), sizeof(argv[i]))) {
				parameters.insert(std::make_pair(MEM_BUDGET_KEY, (unsigned long long int)atoi(context)*(unsigned long long int)1073741824));
				memBudget = (unsigned long long int)atoi(context)*(unsigned long long int)1073741824;
				cout << "MEM_BUDGET_KEY =" << memBudget << endl;
			}
			else if (!strncmp(argv[i], NUM_PARTITION_KEY.c_str(), sizeof(argv[i]))) {
				parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(context)));
				cout << "NUM_PARTITION_KEY =" << atoi(context) << endl;
			}
			else if (!strncmp(argv[i], MAX_EDGES_PER_PARTITION_KEY.c_str(), sizeof(argv[i]))) {
				parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, atoi(context)));
				cout << "MAX_EDGES_PER_PARTITION_KEY =" << atoi(context) << endl;
			}
			else if (!strncmp(argv[i], INSERT_SORT_FLAG.c_str(), sizeof(argv[i]))) {
				if (atoi(context) == 0)
					flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
				else
					flags.insert(std::make_pair(INSERT_SORT_FLAG, true));
				cout << "INSERT_SORT_FLAG =" << atoi(context) << endl;
			}
			else if (!strncmp(argv[i], ALTER_SCHEDULE_FLAG.c_str(), sizeof(argv[i]))) {
				if (atoi(context) == 0)
					flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
				else
					flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, true));
				cout << "ALTER_SCHEDULE_FLAG =" << atoi(context) << endl;
			}
		}
	}
	if (filePath.size() != 2)
		assert(false, "Need a file path ");
}

unsigned long long int Context::getMemBudget() {
	return memBudget;
}

int Context::getNumPartitions() {
	return parameters[NUM_PARTITION_KEY];
}

int Context::getMaxEdges() {
	return parameters[MAX_EDGES_PER_PARTITION_KEY];
}

string Context::getGraphFile() {
	return filePath[INPUT_GRAPH_FILE_KEY];
}
string Context::getGrammarFile() {
	return filePath[GRAMMAR_FILE_KEY];
}
bool Context::getInsertFlag() {
	return flags[INSERT_SORT_FLAG];
}

bool Context::getAlterScheduleFlag() {
	return flags[ALTER_SCHEDULE_FLAG];
}

//void Context::setMemBudget(int memBudget) {
	//parameters[MEM_BUDGET_KEY] = memBudget;
//}
void Context::setNumPartitions(int numPartitions) {
	parameters[NUM_PARTITION_KEY] = numPartitions;
}
void Context::setMaxEdges(int maxEdges) {
	parameters[MAX_EDGES_PER_PARTITION_KEY] = maxEdges;
}

void Context::setInsertFlag(bool flag) {
	flags[INSERT_SORT_FLAG] = flag;
}
void Context::setAlterScheduleFlag(bool flag) {
	flags[ALTER_SCHEDULE_FLAG] = flag;
}
