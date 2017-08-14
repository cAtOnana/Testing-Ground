#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

string outname = "output.txt";
string inname = "MHCC97H_2_trimmed.spectra";
struct spectra
{
	string file_name;
	int scan_no;
	double exp_mh;
	int charge;
	double q_value;
	string seq;
	double calc_mh;
	double mass_shift;
	double raw_score;
	string final_score;
	string modi;
	int spec;
	string prot;
	string posi;
	string label;
	string targe;
	int mc_sites;
	double afm_shift;
	int others;
	int marker = 0;
	bool outputable = true;
	int mut_count = 0;//��¼ͻ��λ�����
};
istream & operator>>(istream & in, vector<spectra> & list_result)
{
	char ch;
	spectra temp;//��Ȼ��ÿ�γ�ʼ���������Ż��»���ÿ�γ�ʼ����ռ��ͬһ�ڴ����򣬴Ӷ�ʹis_mut,modi�ȱ���
				 //ֱ����ֵǰ���ᱣ����һ�ε�ֵ����Ϊ�ڴ�ǡ�ö����ˣ�����˶Ժ��������о��������õ�is_mutֵ����Ӧ����������if else������¸�ֵ
	while (in >> temp.file_name) {
		in >> temp.scan_no;
		in >> temp.exp_mh;
		in >> temp.charge;
		in >> temp.q_value;
		in >> temp.seq;
		in >> temp.calc_mh;
		in >> temp.mass_shift;
		in >> temp.raw_score;
		in >> temp.final_score;
		in.get(ch).get(ch);
		if (ch == '\t')
			temp.modi = "";
		else
		{
			in >> temp.modi;
			//����������ͻ����ʱ�����ð������
			temp.modi=ch+temp.modi;
		}
		in >> temp.spec;
		in >> temp.prot;
		//����������ͻ����ʱ�����ð������

		//temp.prot = temp.prot.substr(temp.prot.find("ENSP"), 15);
		in >> temp.posi;
		in >> temp.label;
		in >> temp.targe;
		in >> temp.mc_sites;
		in >> temp.afm_shift;
		in >> temp.others;
		//������openresearch���ʱ�����ð������
		///in >> temp.mut_count;
		if (temp.q_value >= 0.01 || temp.targe != "target")//�����Ž�������ɸѡ����ֹ���Ҷ�ȡ˳��
			continue;
		list_result.push_back(temp);
	}
	return in;
}
ostream & operator<<(ostream & os, const spectra & s)
{
	os << s.file_name << "	" << s.scan_no << "	" << s.exp_mh << "	" << s.charge << "	" << s.q_value << "	" << s.seq << "	"
		<< s.calc_mh << "	" << s.mass_shift << "	" << s.raw_score << "	" << s.final_score << "\t" << s.modi << "\t" << s.spec
		<< "	" << s.prot << "	" << s.posi << "	" << s.label << "	" << s.targe << "	" << s.mc_sites << "	" << s.afm_shift << "	"
		<< s.others;
	//����������ͻ����ʱ�����ð������
	//os << "	" << s.is_mut;//��������ͻ���ļ��У�ͻ����Ϣ������ENSP��ĩβ���ֶΣ�_SAP_),��ȡensp��ʱ���е����ֶΣ�Ϊ������ļ�������ͻ����ͬ���������������һ���������
	return os;
}
int main() {
	ofstream out(outname);
	for (int i = 0; i < 24; i++) {
		out <<"CHPP_97H_RP"<<i+1<<"_2,";
	}
	out << "|";
	cout << "Done!\n";///
	char c;
	cin >> c;
	
	return 0;
}
