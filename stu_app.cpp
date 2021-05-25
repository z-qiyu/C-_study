#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>


# define STUDENT_MAX_SIZE 128
extern int n = 0;
const char *main_ui_str =  "\n\t\t===== ----- ѧ����Ϣ����ϵͳ ------ ====="
                    "\n----------------------------------------------------------------\n"
                    "\t\t\t[1] ***    ���ѧ����Ϣ         ***\n"
                    "\t\t\t[2] ***    �޸�ѧ����Ϣ         ***\n"
                    "\t\t\t[3] ***    ����ѧ����Ϣ         ***\n"
                    "\t\t\t[4] ***    ɾ��ѧ����Ϣ         ***\n"
					"\t\t\t[5] ***    ����ѧ����Ϣ         ***\n"
                    "\t\t\t[6] ***    չʾ����ѧ����Ϣ     ***\n"
					"\t\t\t[7] ***    ���浽�ļ�(html)     ***\n"
					"\t\t\t[8] ***    ��ȡѧ����Ϣcsv�ļ�  ***\n"
                    "\t\t\t[e] ***    �˳�ϵͳ             ***\n\n"
                    ">>>������ __\b";

struct student
{
    int num;
    char name [15];
    char sex[10];
    char id[15];
	//5+1+1
    float score[7];
}stu[STUDENT_MAX_SIZE];


//������
void main_ui();
//�༭ѧ��˳����еĵ���ѧ����Ϣ
void write_config(struct student &stu);
//ͨ��ѧ�Ų�ѯ���������
int id_for_num(char id[]);
//����ѧ����Ϣs2,��s1
void copy(struct student &s1,struct student &s2);
//ˢ��ѧ������,���ݸ�����n
void stu_num_refresh();
//���ѧ��
void add_stu();
//ɾ��ѧ��
void del_stu();
//�޸�ѧ����Ϣ
void amend_stu();
//����ѧ����Ϣ
void find_stu();
//����ѧ����Ϣ
void ins_stu();
//��ʾѧ����Ϣ
void show_stu(student stu_con);
//��ʾ����ѧ����Ϣ
void show_all_stu();
//ͨ���Ƚ�˳����ָ��Ԫ��Ԫ�أ�������������������
int* rank_array(int score_id);
//����ѧ����Ϣ���ļ�.html
void save_stu();
//Ϊsave_stu������������д��html���
void save_stu_html(fstream &fd,char str_rank[],int sc_num, int sc_5);
//��ȡѧ���ļ���Ϣ
void read_stu_file();


int main(){
    main_ui();
    return 0;
}

/*
  ������
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
			default:cout<<"��������밴��������룡"<<endl;
		}
		cin.get();
	}
}

//����ѧ����Ϣs2,��s1
void copy(struct student &s1,struct student &s2){
	strcpy(s1.name, s2.name);
	strcpy(s1.id, s2.id);
	strcpy(s1.sex, s2.sex);
	s1.num = s2.num;
	for(int i = 0;i<=6;i++){
		s1.score[i] = s2.score[i];
	}
}

//��ѯ��������ţ�û�в�ѯ������-1
int id_for_num(char id[]){
	for(int i = 0;i < STUDENT_MAX_SIZE; i++){
		if(stu[i].num == NULL){
			cout<<"û�����ѧ��!!\n";
			return -1;
		}else{
			if(!strcmp(stu[i].id, id)){
				return i;
			}
		}
	}
	return -1;
}
//�༭ѧ��˳����еĵ���ѧ����Ϣ
void write_config(struct student &stud){
	char id_flag[15];
	cout<<"��������:";
	cin>>stud.name;
	
	int t = 1;
	while(t){
		cout<<"����ѧ��:";
		cin>>id_flag;
		if(n>0){
			for(int k =0;k<n;k++){
				if(!strcmp(id_flag, stu[k].id)){
					cout<<"ѧ���ظ���";
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
	
	cout<<"�����Ա�:";
	cin>>stud.sex;

	cout<<"����ɼ�1:";
	cin>>stud.score[0];
	
	cout<<"����ɼ�2:";
	cin>>stud.score[1];
	
	cout<<"����ɼ�3:";
	cin>>stud.score[2];

	cout<<"����ɼ�4:";
	cin>>stud.score[3];

	cout<<"����ɼ�5:";
	cin>>stud.score[4];

	stud.score[5] = stud.score[0] + stud.score[1] + stud.score[2] + stud.score[3] + stud.score[4];


	float average_marks_stu = (stud.score[0] + stud.score[1] + stud.score[2] + stud.score[3] + stud.score[4])/5;

	stud.score[6] = average_marks_stu;

	stud.num = n+1;
	stu_num_refresh();
	show_stu(stud);
}

/*
  ���ѧ��
*/
void add_stu(){
	int stu_n;
	cout<<"����Ҫ��ӵ�ѧ��������";
	cin>>stu_n;
	int max=n+stu_n;
	for(int i=n;i<max;i++){
		write_config(stu[i]);
	}
}


/*
  ��ʾѧ����Ϣ
*/
void show_stu(student stu_con){
	cout<<"**********************************************************************************************************************\n";
    cout<< stu_con.num << "\t" << stu_con.name << "\t" << stu_con.id << "\t" << stu_con.sex << "\t"<< stu_con.score[0] << "\t" << stu_con.score[1] << "\t" << stu_con.score[2] << "\t" << stu_con.score[3] << "\t" << stu_con.score[4] << "\t" << stu_con.score[5] << "\t" << stu_con.score[6]<<endl;
	cout<<"**********************************************************************************************************************\n";
}



/*
  //ɾ��ѧ��
*/
void del_stu(){
	char i;
	cout<<"-----------------[1] ͨ�����ɾ��------------\n-----------------[2] ͨ��ѧ��ɾ��-----------"<<endl;
	cin>>i;
	if(i == '1'){
		int stu_num_del;
		cout<<"������Ҫɾ����ѧ�������\n_";
		cin>>stu_num_del;
		for(;stu_num_del<=n+1;stu_num_del++){
			copy(stu[stu_num_del-1],stu[stu_num_del]);
		}
		n--;
		stu_num_refresh();
	}else if(i == '2'){
		int del_stu_num;
		char id[15];
		cout<<"������Ҫɾ��ѧ����ѧ��: ";
		cin>>id;
		del_stu_num = id_for_num(id)+1;
		for(;del_stu_num<=n+1;del_stu_num++){
			copy(stu[del_stu_num-1],stu[del_stu_num]);
		}
		n--;
		stu_num_refresh();
		
	}else{
		cout<<"��������밴������룡";
	}

}


/*
  �޸�ѧ����Ϣ
*/
void amend_stu(){
	char i;
	cout<<"-----------------[1] ͨ����Ų�ѯ------------\n-----------------[2] ͨ��ѧ�Ų�ѯ-----------\n";
	cin>>i;
	if(i == '1'){
		int num;
		cout<<"������Ҫ�޸�ѧ�������:\n";
		cin>>num;
		if(num < 1){
			cout<<"�������0����!\n";
		}else{
			if(stu[num-1].id[0] == NULL){
				cout<<"û�����--"<<num;
			}else{
				write_config(stu[num-1]);
			}
		}

	}else if(i == '2'){
		int stu_amend_num;
		char id[15];
		cout<<"������Ҫ�鿴ѧ����ѧ��: ";
		cin>>id;
		stu_amend_num = id_for_num(id);
		write_config(stu[stu_amend_num]);

	}else{
		cout<<"��������밴������룡";
	}
}


//����ѧ����Ϣ
void ins_stu(){
	char i;
	char id_flag[15];
	cout<<"-----------------[1] ͨ����Ų�ѯ����------------\n-----------------[2] ͨ��ѧ�Ų�ѯ����-----------\n_";
	cin>>i;
	if(i == '1'){
		int num_stu;
		cout<<"������Ҫ������ŵ�:_";
		cin>>num_stu;
		if(num_stu > n && num_stu < 0){
			cout<<"�������,���߳�����Χ���밴������룡";
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
		cout<<"��ĳ��ѧ��ǰ���룬���������ѧ��:";
		cin>>id_flag;
		num_stu = id_for_num(id_flag);
		if(num_stu == -1){
			cout<<"û�и�ѧ��!";
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
  ˢ��ѧ������,���ݸ�����n
*/
void stu_num_refresh(){
	int i = 0;
	n = i;
	for(;i<=STUDENT_MAX_SIZE;i++){
		if(strlen(stu[i].id) == 0){
			cout<<"\nˢ�³ɹ�!!!\n"<<"-================��ѧ��"<<n<<"��=================-\n";
			break;
		}
		stu[i].num = i + 1;
		n++;
	}
}


/*
  ��ʾ����ѧ����Ϣ
*/
void show_all_stu(){
	cout<<"���\t"<<"����\t"<<"ѧ��\t\t"<<"�Ա�\t"<<"�ɼ�1\t"<<"�ɼ�2\t"<<"�ɼ�3\t"<<"�ɼ�4\t"<<"�ɼ�5\t"<<"�ܷ�\t"<<"ƽ������\t"<<endl;
	for(int i =0;i<n;i++){
		show_stu(stu[i]);
	}
}

/*
  ����ѧ����Ϣ
*/
void find_stu(){
	char i;
	cout<<"-----------------[1] ͨ����Ų�ѯ------------\n-----------------[2] ͨ��ѧ�Ų�ѯ-----------\n";
	cin>>i;
	if(i == '1'){
		int num;
		cout<<"������Ҫ�鿴ѧ�������:";
		cin>>num;
		if(num < 1){
			cout<<"�������0����!";
		}else{
			if(stu[num-1].id[0] == NULL){
				cout<<"û�����%d!!",num;
			}else{
				show_stu(stu[num-1]);
			}
		}

	}else if(i == '2'){
		int num;
		char id[15];
		cout<<"������Ҫ�鿴ѧ����ѧ��: ";
		cin>>id;
		num = id_for_num(id);
		if(num == -1){
			cout<<"û�����ѧ��!"<<endl;
		}else{
			show_stu(stu[num]);
		}
	}else{
		cout<<"��������밴������룡";
	}
}

//ͨ���Ƚ�˳����ָ��Ԫ��Ԫ�أ�������������������

int* rank_array(int score_id){
	int *M=new int[n];
	//��������M����Ϊѧ������n���ٴ���0��n������������M,M = {0,1,2,......,n-1}
	for(int i=0;i<n;i++){
		M[i] = i;
	}
	
	//ͨ������M���������Ԫ�أ�������ѧ��˳�������ĳɼ�Ԫ��,���óɼ�������M����ð������
	for(i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			if(stu[M[j]].score[score_id] < stu[M[j+1]].score[score_id]){ 
			  int temp =M[j+1];
			  M[j+1] = M[j];
			  M[j] = temp;
			}
		}
	}
	//����M����,��ʱM������ѧ���ɼ��ɴ�С��ѧ���±�����
	return M;
}


//html��������γ�,д���ļ�
void save_stu_html(fstream &fd,char str_rank[],int sc_num, int sc_5){
	int sc_top_90 = 0, sc_89_80 = 0, sc_79_70 = 0, sc_69_60 = 0, sc_60_down = 0;
	int *sc_0 = rank_array(sc_num), i;

	//д��Ĭ������csv�ļ�,
	fd<<" <div class='block'>"<<endl;
	fd<<"<p><font color='#FF0000'>����ʽ��"<<str_rank<<"</font></p>"<<endl;
	fd<<"<table border='1'>\n<tr>\n<th>���</th><th>ѧ��</th><th>����</th><th>�Ա�</th><th>�ɼ�1</th><th>�ɼ�2</th><th>�ɼ�3</th><th>�ɼ�4</th><th>�ɼ�5</th><th>�ܷ�</th><th>ƽ���ɼ�</th>\n</tr>"<<endl;
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
		fd<<"<p><font color='#B22222'>"<<str_rank<<" >90��:   "<<sc_top_90<<"��</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 89-80��:   "<<sc_89_80<<"��</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 79-70��:   "<<sc_79_70<<"��</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" 69-60��:   "<<sc_69_60<<"��</font><p>"<<endl;
		fd<<"<p><font color='#B22222'>"<<str_rank<<" <60��:   "<<sc_60_down<<"��</font><p>"<<endl;
	}
	fd<<"<p><font color='#663366'>"<<str_rank<<"  ƽ������:   "<<average_m<<"</font></p><br><br>"<<endl;
	fd<<" </div>"<<endl;

}

/*
  ����ѧ����Ϣ���ļ�XXX.html
  ����ѧ����Ϣ���ļ�XXX.csv
*/
void save_stu(){
	char file_name[24],file_name_html[24];
	cout<<"�����ļ����ƣ�����Ҫд���׺��:";
	cin>>file_name;
	strcpy(file_name_html,file_name);
	strcat(file_name,".csv");
	strcat(file_name_html,".html");
	fstream fd; 
	fd.open(file_name,ios::out);
	fd<<"���,����,�Ա�,ѧ��,�ɼ�1,�ɼ�2,�ɼ�3,�ɼ�4,�ɼ�5,�ܷ�,ƽ����"<<endl;
	for(int i =0;i<n;i++){
		fd<<stu[i].num<<","<<stu[i].name<<","<<stu[i].sex<<","<<stu[i].id<<","<<stu[i].score[0]<<","<<stu[i].score[1]<<","<<stu[i].score[2]<<","<<stu[i].score[3]<<","<<stu[i].score[4]<<","<<stu[i].score[5]<<","<<stu[i].score[6]<<endl;
	}
	fd.close();


	fd.open(file_name_html,ios::out);

	fd<<"<html>\n <head><title>ѧ�����ӻ�����</title></head>\n\n <body>"<<endl;

	fd<<"<style type='text/css'>\n.block {\nwidth: 620px;\nheight: 80px;\nmargin: 10px;\ndisplay: inline-block;\n}\n</style>"<<endl;
	
	save_stu_html(fd,"�ɼ�1",0, 0);
	save_stu_html(fd,"�ɼ�2",1, 0);
	save_stu_html(fd,"�ɼ�3",2, 0);
	save_stu_html(fd,"�ɼ�4",3, 0);
	save_stu_html(fd,"�ɼ�5",4, 0);
	save_stu_html(fd,"�ֳܷ�ѧ����",6, 0);
	save_stu_html(fd,"�ܷ�",5, 1);
	
	fd<<"\n</body>\n</html>"<<endl;

	fd.close();
}



//��ȡ�ļ����ݴ���
void read_stu_file(){
	char read_file_name[24];
	cout<<"�����ļ����� (�Ӻ�׺) :__";
	cin>>read_file_name;
	ifstream in(read_file_name,ios::nocreate);
	if(!in.is_open()){
		cout<<"�޷����ļ�!!!"<<endl;
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