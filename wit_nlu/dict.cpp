#include "stdafx.h"
#include "dict.h"


dict::dict()
{


	ja2en[u8"私 の 右手 は どう です か"] = "how\%20is\%20my\%20right\%20hand";
	ja2en[u8"私 の 姿勢 を 変える 必要 が あり ます か"] = "do\%20I\%20need\%20to\%20change\%20my\%20posture";
	ja2en[u8"私 の 姿勢 を 修正 する 必要 が あり ます か"] = "do\%20I\%20need\%20to\%20fix\%20my\%20posture";
	ja2en[u8"私 は 何 か を 修正 する 必要 が あり ます か"] = "do\%20I\%20need\%20to\%20correct\%20something";
	ja2en[u8"何 か 変える 必要 な もの が あり ます か"] = "is\%20there\%20anything\%20that\%20I\%20need\%20to\%20change";
	ja2en[u8"私 の 足 を 動かす 必要 が あり ます か"] = "do\%20I\%20need\%20to\%20shift\%20my\%20legs";
	ja2en[u8"私 の 腕 を もっと 曲げる 必要 が あり ます か"] = "do\%20I\%20need\%20to\%20bend\%20my\%20arms\%20more";
	ja2en[u8"これ は 大丈夫 です か"] = "does\%20this\%20look\%20ok";
	ja2en[u8"腕 は 大丈夫 です か"] = "arms\%20ok";
	ja2en[u8"足 は 大丈夫 です か"] = "legs\%20good";
	ja2en[u8"これ は 正しい です か"] = "is\%20this\%20right";
	ja2en[u8"足 です か"] = "the\%20legs";
	ja2en[u8"腕 です か"] = "the\%20arms";
	ja2en[u8"この よう な 腕 です か"] = "arms\%20like\%20this";
	ja2en[u8"腕 は この 高 さ に 上げ まし た か"] = "arms\%20raised\%20this\%20high";
	ja2en[u8"右足 は この よう に 曲げ まし た か"] = "left\%20leg\%20bent\%20like\%20this";
	ja2en[u8"この よう な 左足 です か"] = "left\%20leg\%20this\%20way";
	ja2en[u8"この よう に 立っ て ます か"] = "standing\%20this\%20way";
	ja2en[u8"この よう な 右腕 です か"] = "right\%20arm\%20like\%20this";
	ja2en[u8"この よう な 左腕 です か"] = "with\%20left\%20arm\%20this\%20way";
	ja2en[u8"この よう に し ます か"] = "like\%20so";
	ja2en[u8"私 は 間違っ て い ます か"] = "am\%20I\%20doing\%20this\%20wrong";
	ja2en[u8"私 は 正しい です か"] = "am\%20I\%20doing\%20this\%20correctly";
	ja2en[u8"私 の 右足 は 今 大丈夫 です か"] = "do\%20my\%20right\%20leg\%20look\%20good\%20now";
	ja2en[u8"私 の 足 は 今 大丈夫 です か"] = "do\%20my\%20arms\%20look\%20ok\%20now";
	ja2en[u8"これ が 正しい と 思い ます か"] = "do\%20you\%20think\%20this\%20is\%20correct";
	ja2en[u8"私 の 左腕 は どう です か"] = "how\%20does\%20my\%20left\%20arm\%20look\%20now";
	ja2en[u8"これ は どう です か"] = "how\%20does\%20this\%20look";
	ja2en[u8"これ が どう 思い ます か"] = "what\%20do\%20you\%20think\%20of\%20this";
	ja2en[u8"私 の 姿勢 は どう 思い ます か"] = "what\%20do\%20you\%20think\%20of\%20my\%20posture";
	ja2en[u8"正しい 場合 は 言っ て ください"] = "can\%20you\%20tell\%20me\%20if\%20this\%20is\%20good";
	ja2en[u8"私 の 左足 が 正しく ない 場合 は 言っ て ください"] = "can\%20you\%20let\%20me\%20know\%20if\%20my\%20left\%20leg\%20is\%20incorrect";
	ja2en[u8"私 の 腕 が 間違っ て いる 場合 は 言っ て ください"] = "can\%20you\%20tell\%20me\%20if\%20my\%20arms\%20are\%20wrong";
	ja2en[u8"私 の 右腕 は 正しい です か"] = "is\%20my\%20right\%20arm\%20correct";
	ja2en[u8"私 の 足 は 間違っ て い ます か"] = "are\%20my\%20legs\%20wrong";
	ja2en[u8"私 の 腕 は 間違っ て い ます か"] = "are\%20my\%20arms\%20incorrect";
	ja2en[u8"私 の 左腕 が 正しく あり ませ ん か"] = "is\%20my\%20left\%20arm\%20incorrect";
	ja2en[u8"私 の 左足 が 正しく あり ませ ん か"] = "is\%20my\%20left\%20leg\%20incorrect";
	ja2en[u8"私 の 右足 が 正しく あり ませ ん か"] = "is\%20my\%20right\%20leg\%20incorrect";
	ja2en[u8"私 の 右足 が 間違っ て い ます か"] = "is\%20my\%20right\%20leg\%20wrong";
	ja2en[u8"私 の 左足 が 間違っ て い ます か"] = "is\%20my\%20left\%20leg\%20wrong";
	ja2en[u8"私 の 左腕 は 間違っ て い ます か"] = "is\%20my\%20left\%20arm\%20wrong";
	ja2en[u8"私 の 右腕 は 間違っ て い ます か"] = "is\%20my\%20right\%20arm\%20wrong";
	ja2en[u8"何 が 間違っ て い ます か"] = "What's\%20wrong";
	ja2en[u8"私 の 右腕 は どう です か"] = "how\%20is\%20my\%20right\%20arm";
	ja2en[u8"私 の 右足 は どう です か"] = "how\%20is\%20my\%20right\%20leg";
	ja2en[u8"私 の 左足 は どう です か"] = "how\%20is\%20my\%20left\%20leg";
	ja2en[u8"これ は"] = "and\%20this";
	ja2en[u8"私 の 右腕 は 良い です か"] = "is\%20my\%20right\%20arm\%20good";
	ja2en[u8"右腕 は 大丈夫 です か"] = "is\%20the\%20right\%20arm\%20good";
	ja2en[u8"左腕 は 大丈夫 です か"] = "is\%20the\%20left\%20arm\%20alright";
	ja2en[u8"左足 は 大丈夫 です か"] = "is\%20the\%20left\%20leg\%20good";
	ja2en[u8"左腕 は どう です か"] = "how\%20is\%20the\%20left\%20arm";
	ja2en[u8"私 の 左腕 は 大丈夫 です か"] = "is\%20my\%20left\%20arm\%20good";
	ja2en[u8"私 の 左腕 は 正しい です か"] = "is\%20my\%20left\%20arm\%20correct";
	ja2en[u8"これ です か"] = "this";
	ja2en[u8"右足 は 大丈夫 です か"] = "is\%20the\%20right\%20leg\%20good";
	ja2en[u8"姿勢"] = "posture";
	ja2en[u8"左足 は"] = "left\%20leg";
	ja2en[u8"右足 は"] = "right\%20leg";
	ja2en[u8"左腕 は"] = "left\%20arm";
	ja2en[u8"右腕 は"] = "right\%20arm";
	ja2en[u8"こう です か"] = "like\%20this";
	ja2en[u8"私 の 姿勢 は 正しい です か"] = "is\%20my\%20body\%20position\%20correct";
	ja2en[u8"私 の 右腕 の ポジション は 正しい です か"] = "is\%20my\%20right\%20arm\%20position\%20correct";
	ja2en[u8"私 の 右足 は 大丈夫 です か"] = "is\%20my\%20right\%20leg\%20good";
	ja2en[u8"私 が やっ て いる こと は 正しい です か"] = "am\%20I\%20doing\%20this\%20right";
	ja2en[u8"私 の 左足 は 大丈夫 です か"] = "is\%20my\%20left\%20leg\%20ok";
	ja2en[u8"私 の 腕 は どう です か"] = "how\%20are\%20my\%20arms";
	ja2en[u8"私 の 足 は 大丈夫 です か"] = "are\%20my\%20legs\%20ok";
	ja2en[u8"私 の 姿勢 は どう です か"] = "how\%20is\%20my\%20posture";



}

std::vector<std::string> split_string(std::string text) {
	std::stringstream ss(text);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	return vstrings;
}


int count_a_in_b(std::vector<std::string> &a, std::vector<std::string> &b) {
	int count = 0;
	for (int i = 0; i< a.size(); i++) {
		for (int j = 0; j<b.size(); j++) {
			if (a[i] == b[j]) {
				//std::cout << a[i] << " is in" << std::endl;
				count += 1;
			}
		}
	}
	std::cout << count << std::endl;
	return count;

}

void StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;
}

std::string dict::getEn(std::string ja)
{
	typedef std::map<std::string, std::string>::const_iterator it_type; 
	
	float max_score;
	float score;
	
	std::string k;
	std::vector<std::string> vk;
		
	std::vector<std::string> vja;
	vja = split_string(ja);
	
	max_score = 0;
	std::string ret;
	int a = 0;

	//get score of japanese query - keys in ja2en
	//for all map entries
	for (it_type iterator = ja2en.begin(); iterator != ja2en.end(); iterator++) {
		a += 1;
		k = iterator->first;
		std::cout << std::endl << k << std::endl;
		vk = split_string(k);
		
		score = 0;
		
		// check word membership
		/*for (int i = 0; i < vja.size(); i++) {
			for (int j = 0; j < vk.size(); j++) {
				if (vk[j] == vja[i]) {
					std::cout << vja[i] << " is in " << k << std::endl;
					score += 1;
				}
			}
			//if (k.find(" " + vja[i] + " ") != std::string::npos) {
				
				//std::cout << vja[i] << " is in " << k << std::endl;
				//score += 1;
			//}
		}*/
		score = (float)count_a_in_b(vja, vk) / (vja.size() - 1);

		if (score > max_score) {
			max_score = score;
			ret = iterator->second;

			std::cout << "YEAH ";
			printf("%f ", max_score);
			std::cout << ret << std::endl << std::endl;
			//std::cout << "new highest score of  from the key " + ret <<  std::endl;
		}
	} 
	std::cout << a << std::endl;
	std::cout << "ja2en.size() is " << ja2en.size() << '\n';
	return ret;
}

std::vector<std::string> dict::getVec(std::string text)
{
	std::vector<std::string> vtext;

	std::istringstream iss(text);

	while (iss) {
		std::string word;
		iss >> word;
		vtext.push_back(word);
	}

	return vtext;
}
