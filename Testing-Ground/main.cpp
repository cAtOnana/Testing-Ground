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
	int mut_count = 0;//记录突变位点个数
};
istream & operator>>(istream & in, vector<spectra> & list_result)
{
	char ch;
	spectra temp;//虽然是每次初始化，但在优化下会变成每次初始化都占用同一内存区域，从而使is_mut,modi等变量
				 //直到赋值前都会保留上一次的值（因为内存恰好对上了）；因此对后续步骤有决定性作用的is_mut值，更应该用完整的if else语句重新赋值
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
			//当处理理论突变结果时，启用暗绿语句
			temp.modi=ch+temp.modi;
		}
		in >> temp.spec;
		in >> temp.prot;
		//当处理理论突变结果时，启用暗绿语句

		//temp.prot = temp.prot.substr(temp.prot.find("ENSP"), 15);
		in >> temp.posi;
		in >> temp.label;
		in >> temp.targe;
		in >> temp.mc_sites;
		in >> temp.afm_shift;
		in >> temp.others;
		//当处理openresearch结果时，启用暗绿语句
		///in >> temp.mut_count;
		if (temp.q_value >= 0.01 || temp.targe != "target")//在最后才进行条件筛选，防止打乱读取顺序
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
	//当处理理论突变结果时，启用暗绿语句
	//os << "	" << s.is_mut;//由于理论突变文件中，突变信息隐含在ENSP号末尾的字段（_SAP_),且取ensp号时会切掉此字段，为在输出文件中区分突变链同正常链，故在最后一列输出此项
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
