#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<stack>
// So luong mang
#define soluong 7
// so luong hang dong
#define HD 4
using namespace std;
	
const char* action[]={"first State","Yello frog jump 1 step","Yello frog jump 2 steps","Green frog jump 1 step","Green frog jump 2 steps"};
	
//Khai bai file de ghi du lieu
FILE *filePrint= fopen("bai1.txt","wt");
	
typedef struct{
	int mang[soluong];
	int vitri;
}State;
	
void printState(State state){
	int i;
	for(i=0;i<soluong;i++){
		if (state.mang[i] == 1) {
			printf("Ech_Vang");
			fprintf(filePrint,"Ech_Vang");
		}
		else if (state.mang[i] == 2) {
			printf("Ech_Xanh");
			fprintf(filePrint,"Ech_Xanh");
		}
		else {
			printf("%d", state.mang[i]);
			fprintf(filePrint,"%d",state.mang[i]);
		}
		printf(",");
		fprintf(filePrint,",");
	}
	printf("\n");
	fprintf(filePrint,"\n");
}
	
// Ech Xanh nhay 1 buoc ve phia truoc
int echXanhNhay1(State state,State *result){
	*result = state;
	int vitri = state.vitri;
	if (state.mang[vitri-1] == 2){
		result->mang[vitri]   = 2;
		result->mang[vitri-1] = 0;
		result->vitri = vitri-1;
		return 1;
	}
	return 0;
}
	
// Ech Xanh nhay 2 buoc ve phia truoc
int echXanhNhay2(State state, State *result){
	*result = state;
	int vitri = state.vitri;
	if((state.mang[vitri-1] == 1)&&(state.mang[vitri-2] == 2)){
		result->mang[vitri] = 2;
		result->mang[vitri-2] = 0;
		result->vitri = vitri-2;
		return 1;
	}
	return 0;
}
	
// Ech Vang nhay 1 buoc ve phia truoc
int echVangNhay1(State state,State *result){
	*result = state;
	int vitri = state.vitri;
	if(state.mang[vitri+1] == 1){
		result->mang[vitri] = 1;
		result->mang[vitri+1] = 0;
		result->vitri = vitri+1;
		return 1;
	}	
	return 0;
}

// Ech Vang nhay 2 buoc ve phia truoc
int echVangNhay2(State state, State *result){
	*result = state;
	int vitri = state.vitri;
	if((state.mang[vitri+1]==2) && (state.mang[vitri+2]==1)){
		result->mang[vitri] = 1;
		result->mang[vitri+2] = 0;
		result->vitri = vitri+2;
		return 1;
	}
	return 0;
}

//Goi hanh dong	
int call_Operator(State state,State *result,int option){
	switch(option){
		case 1: return echVangNhay1(state,result);
		case 2: return echVangNhay2(state,result);
		case 3: return echXanhNhay1(state,result);
		case 4: return echXanhNhay2(state,result);
		default: printf("\nError calls operator");
		return 0; 
	}
}
//----------------------
typedef struct Node{
	State state;
	struct Node* parent;
	int noFunction;
}Node;
//So sanh hai trang thai	
int compareStates(State a, State b){
	int i;
	for (i=0;i<soluong;i++)
		if(a.mang[i] != b.mang[i]) return 0;
			return 1;
}

//Kiem tra co phai la trang thai muc tieu hay khong?
int goalcheck(State a,State b){
	return compareStates(a,b);
}

//Ham tim trang thai
int find_State_DFS(State state,stack<Node*> openStack){
	while(!openStack.empty()){
		if(compareStates(openStack.top()->state,state))
			return 1;
		openStack.pop();
	}
	return 0;
}
//Giai thuat tim kiem theo chiều sâu
Node* DFS_Algorithm(State state,State g){
	//Khoi tao 2 danh sach: Open_DFS,Close_DFS
	stack<Node*> Open_DFS;
	stack<Node*> Close_DFS;

	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state=state;
	root->parent=NULL;
	root->noFunction = 0;
			
	//Dua nut cha vao danh sach Open_DFS
	Open_DFS.push(root);
	while(!Open_DFS.empty()){	//Lay 1 dinh trong danh sach Open_DFS, xoa dinh do va dua dinh do vao Close_DFS
		Node* node = Open_DFS.top();
		Open_DFS.pop();
		Close_DFS.push(node);
		//Kiem tra xem dinh lay ra co phai la trang thai muc tieu khong?
		if(goalcheck(node->state,g))
			return node;
		int opt;
		//goi phep toan tren trang thai
		for(opt=1; opt<=HD; opt++){
			State newstate;		
			if(call_Operator(node->state,&newstate,opt)){
				//Neu trang thai sinh ra da ton tai thi bo qua
				if(find_State_DFS(newstate,Close_DFS) || find_State_DFS(newstate,Open_DFS) )
					continue;
				//Neu trang thai moi chua ton tai thi them vao Open_DFS
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->noFunction = opt;
				newNode->parent = node;
				newNode->state = newstate;						
				Open_DFS.push(newNode);
			}					
		}				
	}
			
	return NULL;
}

//Ham in ket qua tim kiem
void print_WaysToGetGoal_DFS(Node* node){
	stack<Node*> stackprint;			
	while(node->parent != NULL){
		stackprint.push(node);
		node = node->parent;
	}
	stackprint.push(node);
	int no_action=0;
	while(!stackprint.empty()){
		printf("Action %d: %s\n",no_action,action[stackprint.top()->noFunction]);
		fprintf(filePrint,"Action %d: %s\n",no_action,action[stackprint.top()->noFunction]);
		printState(stackprint.top()->state);
		stackprint.pop();
		no_action++;						
	}			
}

//Chuong trinh chinh
int main(){
	State start, end;
	start.vitri = 3;
	start.mang[0]=2;
	start.mang[1]=2;
	start.mang[2]=2;
	start.mang[3]=0;
	start.mang[4]=1;
	start.mang[5]=1;
	start.mang[6]=1;
		
	end.vitri=3;
	end.mang[0]=1;
	end.mang[1]=1;
	end.mang[2]=1;
	end.mang[3]=0;
	end.mang[4]=2;
	end.mang[5]=2;
	end.mang[6]=2;
		
		
	Node* p = DFS_Algorithm(start, end);
	print_WaysToGetGoal_DFS(p);
		
	fclose(filePrint);
	return EXIT_SUCCESS;
	return 0;
	
}
