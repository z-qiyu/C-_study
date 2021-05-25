#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>


# define STUDENT_MAX_SIZE 128
extern int n = 0;
const char *main_ui_str =  "\n\t\t===== ----- 学生信息管理系统 ------ ====="
                    "\n----------------------------------------------------------------\n"
                    "\t\t\t[1] ***    添加学生信息         ***\n"
                    "\t\t\t[2] ***    修改学生信息         ***\n"
                    "\t\t\t[3] ***    查找学生信息         ***\n"
                    "\t\t\t[4] ***    删除学生信息         ***\n"
					"\t\t\t[5] ***    插入学生信息         ***\n"
                    "\t\t\t[6] ***    展示所有学生信息     ***\n"
					"\t\t\t[7] ***    保存到文件(html)     ***\n"
					"\t\t\t[8] ***    读取学生信息csv文件  ***\n"
                    "\t\t\t[e] ***    退出系统             ***\n\n"
                    ">>>请输入 __\b";

struct student
{
    int num;
    char name [15];
    char sex[10];
    char id[15];
	//5+1+1
    float score[7];
}stu[STUDENT_MAX_SIZE];


//主界面
void main_ui();
//编辑学生顺序表中的单个学生信息
void write_config(struct student &stu);
//通过学号查询，返回序号
int id_for_num(char id[]);
//复制学生信息s2,到s1
void copy(struct student &s1,struct student &s2);
//刷新学生个数,传递给变量n
void stu_num_refresh();
//添加学生
void add_stu();
//删除学生
void del_stu();
//修改学生信息
void amend_stu();
//查找学生信息
void find_stu();
//插入学生信息
void ins_stu();
//显示学生信息
void show_stu(student stu_con);
//显示所有学生信息
void show_all_stu();
//通过比较顺序表的指定元素元素，来创建用于排序数组
int* rank_array(int score_id);
//保存学生信息到文件.html
void save_stu();
//为save_stu（）函数服务，写入html表格
void save_stu_html(fstream &fd,char str_rank[],int sc_num, int sc_5);
//读取学生文件信息
void read_stu_file();


int main(){
    main_ui();
    return 0;
}

/*
  主界面
*/

void main_ui(){
	int t_f = 1;
	while (t_f){
		cout<<main_ui_str;
		char run;
		cin>>run;
		switch(run){
			case'1':add_stu();break;
			case'2':amend_stu();break;
			case'3':find_stu();break;
			case'4':del_stu();break;
			case'5':ins_stu();break;
			case'6':cout<<"\n\n";show_all_stu();cout<<"\n\n";break;
			case'7':save_stu();break;
			case'8':read_stu_file();break;
			case'9':stu_num_refresh();break;
			case'e':t_f = 0;break;
			default:cout<<"输入错误，请按规矩来输入！"<<endl;
		}
		cin.get();
	}
}

//复制学生信息s2,到s1
void copy(struct student &s1,struct student &s2){
	strcpy(s1.name, s2.name);
	strcpy(s1.id, s2.id);
	strcpy(s1.sex, s2.sex);
	s1.num = s2.num;
	for(int i = 0;i<=6;i++){
		s1.score[i] = s2.score[i];
	}
}

//查询到返回序号，没有查询到返回-1
int id_for_num(char id[]){
	for(int i = 0;i < STUDENT_MAX_SIZE; i++){
		if(stu[i].num == NULL){
			cout<<"没有这个学号!!\n";
			return -1;
		}else{
			if(!strcmp(stu[i].id, id)){
				return i;
			}
		}
	}
	return -1;
}
//编辑学生顺序表中的单个学生信息
void write_config(struct student &stud){
	char id_flag[15];
	cout<<"输入姓名:";
	cin>>stud.name;
	
	int t = 1;
	while(t){
		cout<<"输入学号:";
		cin>>id_flag;
		if(n>0){
			for(int k =0;k<n;k++){
				if(!strcmp(id_flag, stu[k].id)){
					cout<<"学号重复！";
					break;
				}else{
					if(k==n-1){
						 strcpy(stud.id, id_flag);
						 t=0;
					}
				}
			}
		}else{
			strcpy(stud.id, id_flag);
			t=0;
		}
	}
	
	cout<<"输入性别:";
	cin>>stud.sex;

	cout<<"输入成绩1:";
	cin>>stud.score[0];
	
	cout<<"输入成绩2:";
	cin>>stud.score[1];
	
	cout<<"输入成绩3:";
	cin>>stud.score[2];

	cout<<"输入成绩4:";
	cin>>stud.score[3];

	cout<<"输入成绩5:";
	cin>>stud.score[4];

	stud.score[5] = stud.score[0] + stud.score[1] + stud.score[2] + stud.score[3] + stud.score[4];


	float average_marks_stu = (stud.score[0] + stud.score[1] + stud.score[2] + stud.score[3] + stud.score[4])/5;

	stud.score[6] = average_marks_stu;

	stud.num = n+1;
	stu_num_refresh();
	show_stu(stud);
}

/*
  添加学生
*/
void add_stu(){
	int stu_n;
	cout<<"输入要添加的学生个数：";
	cin>>stu_n;
	int max=n+stu_n;
	for(int i=n;i<max;i++){
		write_config(stu[i]);
	}
}


/*
  显示学生信息
*/
void show_stu(student stu_con){
	cout<<"**********************************************************************************************************************\n";
    cout<< stu_con.num << "\t" << stu_con.name << "\t" << stu_con.id << "\t" << stu_con.sex << "\t"<< stu_con.score[0] << "\t" << stu_con.score[1] << "\t" << stu_con.score[2] << "\t" << stu_con.score[3] << "\t" << stu_con.score[4] << "\t" << stu_con.score[5] << "\t" << stu_con.score[6]<<endl;
	cout<<"**********************************************************************************************************************\n";
}



/*
  //删除学生
*/
void del_stu(){
	char i;
	cout<<"-----------------[1] 通过序号删除------------\n-----------------[2] 通过学号删除-----------"<<endl;
	cin>>i;
	if(i == '1'){
		int stu_num_del;
		cout<<"请输入要删除的学生的序号\n_";
		cin>>stu_num_del;
		for(;stu_num_del<=n+1;stu_num_del++){
			copy(stu[stu_num_del-1],stu[stu_num_del]);
		}
		n--;
		stu_num_refresh();
	}else if(i == '2'){
		int del_stu_num;
		char id[15];
		cout<<"输入需要删除学生的学号: ";
		cin>>id;
		del_stu_num = id_for_num(id)+1;
		for(;del_stu_num<=n+1;del_stu_num++){
			copy(stu[del_stu_num-1],stu[del_stu_num]);
		}
		n--;
		stu_num_refresh();
		
	}else{
		cout<<"输入错误，请按规矩输入！";
	}

}


/*
  修改学生信息
*/
void amend_stu(){
	char i;
	cout<<"-----------------[1] 通过序号查询------------\n-----------------[2] 通过学号查询-----------\n";
	cin>>i;
	if(i == '1'){
		int num;
		cout<<"输入需要修改学生的序号:\n";
		cin>>num;
		if(num < 1){
			cout<<"输入大于0的数!\n";
		}else{
			if(stu[num-1].id[0] == NULL){
				cout<<"没有序号--"<<num;
			}else{
				write_config(stu[num-1]);
			}
		}

	}else if(i == '2'){
		int stu_amend_num;
		char id[15];
		cout<<"输入需要查看学生的学号: ";
		cin>>id;
		stu_amend_num = id_for_num(id);
		write_config(stu[stu_amend_num]);

	}else{
		cout<<"输入错误，请按规矩输入！";
	}
}


//插入学生信息
void ins_stu(){
	char i;
	char id_flag[15];
	cout<<"-----------------[1] 通过序号查询插入------------\n-----------------[2] 通过学号查询插入-----------\n_";
	cin>>i;
	if(i == '1'){
		int num_stu;
		cout<<"输入需要插入序号的:_";
		cin>>num_stu;
		if(num_stu > n && num_stu < 0){
			cout<<"输入错误,或者超出范围，请按规矩输入！";
		}else{
			for(int i=n-1;i>=num_stu-1;i--){
				copy(stu[i+1],stu[i]);
			}
			n++;
			i = num_stu-1;
			write_config(stu[i]);

		}
	}else if(i == '2'){
		int num_stu;
		cout<<"在某个学号前插入，请输入这个学号:";
		cin>>id_flag;
		num_stu = id_for_num(id_flag);
		if(num_stu == -1){
			cout<<"没有该学号!";
		}else{
			for(int i=n-1;i>=num_stu-1;i--){
				copy(stu[i+1],stu[i]);
			}
			i = num_stu-1;
			write_config(stu[i]);
		}
	}
	stu_num_refresh();
}


/*
  刷新学生个数,传递给变量n
*/
void stu_num_refresh(){
	int i = 0;
	n = i;
	for(;i<=STUDENT_MAX_SIZE;i++){
		if(strlen(stu[i].id) == 0){
			cout<<"\n刷新成功!!!\n"<<"-================有学生"<<n<<"人=================-\n";
			break;
		}
		stu[i].num = i + 1;
		n++;
	}
}


/*
  显示所有学生信息
*/
void show_all_stu(){
	cout<<"序号\t"<<"姓名\t"<<"学号\t\t"<<"性别\t"<<"成绩1\t"<<"成绩2\t"<<"成绩3\t"<<"成绩4\t"<<"成绩5\t"<<"总分\t"<<"平均分数\t"<<endl;
	for(int i =0;i<n;i++){
		show_stu(stu[i]);
	}
}

/*
  查找学生信息
*/
void find_stu(){
	char i;
	cout<<"-----------------[1] 通过序号查询------------\n-----------------[2] 通过学号查询-----------\n";
	cin>>i;
	if(i == '1'){
		int num;
		cout<<"输入需要查看学生的序号:";
		cin>>num;
		if(num < 1){
			cout<<"输入大于0的数!";
		}else{
			if(stu[num-1].id[0] == NULL){
				cout<<"没有序号%d!!",num;
			}else{
				show_stu(stu[num-1]);
			}
		}

	}else if(i == '2'){
		int num;
		char id[15];
		cout<<"输入需要查看学生的学号: ";
		cin>>id;
		num = id_for_num(id);
		if(num == -1){
			cout<<"没有这个学号!"<<endl;
		}else{
			show_stu(stu[num]);
		}
	}else{
		cout<<"输入错误，请按规矩输入！";
	}
}

//通过比较顺序表的指定元素元素，来创建用于排序数组

int* rank_array(int score_id){
	int *M=new int[n];
	//创建数组M长度为学生人数n，再存入0到n连续的整数到M,M = {0,1,2,......,n-1}
	for(int i=0;i<n;i++){
		M[i] = i;
	}
	
	//通过遍历M里面的整型元素，来访问学生顺序表里面的成绩元素,利用成绩，来对M排序（冒泡排序）
	for(i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			if(stu[M[j]].score[score_id] < stu[M[j+1]].score[score_id]){ 
			  int temp =M[j+1];
			  M[j+1] = M[j];
			  M[j] = temp;
			}
		}
	}
	//返回M数组,此时M数组是学生成绩由大到小的学生下标序列
	return M;
}


//html单个表格形成,写入文件
void save_stu_html(fstream &fd,char str_rank[],int sc_num, int sc_5){
	int sc_top_90 = 0, sc_89_80 = 0, sc_79_70 = 0, sc_69_60 = 0, sc_60_down = 0;
	int *sc_0 = rank_array(sc_num), i;

	//写入默认排序到csv文件,
	fd<<" <div class='block'>"<<endl;
	fd<<"<p><font color='#FF0000'>排序方式："<<str_rank<<"</font></p>"<<endl;
	fd<<"<table border='1'>\n<tr>\n<th>序号</th><th>学号</th><th>姓名</th><th>性别</th><th>成绩1</th><th>成绩2</th><th>成绩3</th><th>成绩4</th><th>成绩5</th><th>总分</th><th>平均成绩</th>\n</tr>"<<endl;
	for(int j=0;j<n;j++){
		i = sc_0[j];
		if (stu[i].score[sc_num]>=90){
			sc_top_90 = sc_top_90 + 1;
		}else if(stu[i].score[sc_num]>=80 && stu[i].score[sc_num]<90){
			sc_89_80 = sc_89_80 + 1;
		}else if(stu[i].score[sc_num]>=70 && stu[i].score[sc_num]<80){
			sc_79_70 = sc_79_70 + 1;
		}else if(stu[i].score[sc_num]>=60 && stu[i].score[sc_num]<70){
			sc_69_60 = sc_69_60 +1;
		}else{
			sc_60_down = sc_60_down +1;
		}
		fd<<" <tr>"<<endl;
		fd<<"  <th><font color='#D2691E'>"<<j+1<<"</font></th>"<<endl;
		fd<<"  <th><font color='#C71585'>"<<stu[i].id<<"</font></th>"<<endl;
		fd<<"  <th><font color='#8A2BE2'>"<<stu[i].name<<"</font></th>"<<endl;
		fd<<"  <th><font color='#D8B0000'>"<<stu[i].sex<<"</font></th>"<<endl;
		fd<<"  <th><font color='#DA70D6'>"<<stu[i].score[0]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#DAA520'>"<<stu[i].score[1]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#DB7093'>"<<stu[i].score[2]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#DC143C'>"<<stu[i].score[3]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#4B0082'>"<<stu[i].score[4]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#FF3333'>"<<stu[i].score[5]<<"</font></th>"<<endl;
		fd<<"  <th><font color='#F08080'>"<<stu[i].score[6]<<"</font></th>"<<endl;
		fd<<" </tr>"<<endl;
	}
	fd<<"</table>"<<endl;
	float average_m = 0;
	for(j=0;j<n;j++){
		cout<<average_m<<endl;
		average_m = average_m + stu[j].score[sc_num];
	}
	
	average_m = average_m/n;
	if(!sc_5){
		fd<<"<p><font color='#B22222'>"<<str_rank<<" >90分:   "<<sc_top_90<<"人</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 89-80分:   "<<sc_89_80<<"人</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 79-70分:   "<<sc_79_70<<"人</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 69-60分:   "<<sc_69_60<<"人</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" <60分:   "<<sc_60_down<<"人</font><p>"<<endl;
	}
	fd<<"<p><font color='#663366'>"<<str_rank<<"  平均分数:   "<<average_m<<"</font></p><br><br>"<<endl;
	fd<<" </div>"<<endl;

}

/*
  保存学生信息到文件XXX.html
  保存学生信息到文件XXX.csv
*/
void save_stu(){
	char file_name[24],file_name_html[24];
	cout<<"输入文件名称，不需要写入后缀名:";
	cin>>file_name;
	strcpy(file_name_html,file_name);
	strcat(file_name,".csv");
	strcat(file_name_html,".html");
	fstream fd; 
	fd.open(file_name,ios::out);
	fd<<"序号,姓名,性别,学号,成绩1,成绩2,成绩3,成绩4,成绩5,总分,平均分"<<endl;
	for(int i =0;i<n;i++){
		fd<<stu[i].num<<","<<stu[i].name<<","<<stu[i].sex<<","<<stu[i].id<<","<<stu[i].score[0]<<","<<stu[i].score[1]<<","<<stu[i].score[2]<<","<<stu[i].score[3]<<","<<stu[i].score[4]<<","<<stu[i].score[5]<<","<<stu[i].score[6]<<endl;
	}
	fd.close();


	fd.open(file_name_html,ios::out);

	fd<<"<html>\n <head><title>学生可视化数据</title></head>\n\n <body>"<<endl;

	fd<<"<style type='text/css'>\n.block {\nwidth: 620px;\nheight: 80px;\nmargin: 10px;\ndisplay: inline-block;\n}\n</style>"<<endl;
	
	save_stu_html(fd,"成绩1",0, 0);
	save_stu_html(fd,"成绩2",1, 0);
	save_stu_html(fd,"成绩3",2, 0);
	save_stu_html(fd,"成绩4",3, 0);
	save_stu_html(fd,"成绩5",4, 0);
	save_stu_html(fd,"总分除学科数",6, 0);
	save_stu_html(fd,"总分",5, 1);
	
	fd<<"\n</body>\n</html>"<<endl;

	fd.close();
}



//读取文件到暂存器
void read_stu_file(){
	char read_file_name[24];
	cout<<"输入文件名称 (加后缀) :__";
	cin>>read_file_name;
	ifstream in(read_file_name,ios::nocreate);
	if(!in.is_open()){
		cout<<"无法打开文件!!!"<<endl;
	}else{
		char line[128];
		int i=-1;
		while(!in.eof()){
			in.getline(line,100);
			if(strlen(line) == 0){
				break;
			}
			if (i==-1){
				i++;
				continue;
			}
			int a,flag=0;
			cout<<line<<endl;

			//num
			for(a=0;a<128;a++){
				if (line[a]==','){
					char line_num[3];
					for(int k=flag;k<a;k++){
						line_num[k] = line[k];
						cout<<line_num[k];

					}
					stu[i].num = atoi(line_num);
					cout<<stu[i].num<<endl;
					break;
				}
			}
			a++;
			flag=a;
			cout<<endl;
			
			//name
			for(;a<128;a++){
				if (line[a]==','){
					int o=0;
					for(int k=flag;k<a;k++){
						stu[i].name[o] = line[k];
						cout<<line[k];
						o++;
					}
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//sex
			for(;a<128;a++){
				if (line[a]==','){
					int o=0;
					for(int k=flag;k<a;k++){
						stu[i].sex[o] = line[k];
						cout<<line[k];
						o++;
					}
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//id
			for(;a<128;a++){
				if (line[a]==','){
					int o=0;
					for(int k=flag;k<a;k++){
						stu[i].id[o] = line[k];
						cout<<line[k];
						o++;
					}

					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//score1
			for(;a<128;a++){
				if (line[a]==','){
					char line_s1[8] = {0};
					int o=0;
					for(int k=flag;k<a;k++){
						line_s1[o] = line[k];
						cout<<line[k];
						o++;
					}
					stu[i].score[0] = (float)atof(line_s1);
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//score2
			for(;a<128;a++){
				if (line[a]==','){
					char line_s1[8] = {0};
					int o=0;
					for(int k=flag;k<a;k++){
						line_s1[o] = line[k];
						cout<<line[k];
						o++;
					}
					stu[i].score[1] = (float)atof(line_s1);
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//score3
			for(;a<128;a++){
				if (line[a]==','){
					char line_s1[8] = {0};
					int o=0;
					for(int k=flag;k<a;k++){
						line_s1[o] = line[k];
						cout<<line[k];
						o++;
					}
					stu[i].score[2] = (float)atof(line_s1);
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//score4
			for(;a<128;a++){
				if (line[a]==','){
					char line_s1[8] = {0};
					int o=0;
					for(int k=flag;k<a;k++){
						line_s1[o] = line[k];
						cout<<line[k];
						o++;
					}
					stu[i].score[3] = (float)atof(line_s1);
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//score5
			for(;a<128;a++){
				if (line[a]==','){
					char line_s1[8] = {0};
					int o=0;
					for(int k=flag;k<a;k++){
						line_s1[o] = line[k];
						cout<<line[k];
						o++;
					}
					stu[i].score[4] = (float)atof(line_s1);
					break;
				}
			}
			a++;
			flag = a;
			cout<<endl;
			
			//total score
			stu[i].score[5] = stu[i].score[0] + stu[i].score[1] + stu[i].score[2] + stu[i].score[3] + stu[i].score[4];


			float average_marks_stu = (stu[i].score[5])/5;

			stu[i].score[6] = average_marks_stu;	
			//average score

			
			i++;
			n++;
		}
		
		stu_num_refresh();
		in.close();

	}
}