#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <ostream>
using namespace std;

int size = 30000;
int * C;
const int max_occurs = 30;
int occurs[max_occurs];

int str2int(string s){
	int ret = 0;
	stringstream geek(s);
	geek >> ret;
	return ret;
}
double str2dub(string s){
	double ret;
	char buffer[20];
	int Dsize = s.length();
	for(int i = 0; i < Dsize; i++)
		buffer[i] = s[i];
	ret = atof(buffer);
	return ret;
}

string trunc(string s){
	int o_size  = s.length()-1;
	int n_size = o_size + 1;
	for(int i = o_size; i > 0; i--){
		if(s[i] != ' ') break;
		n_size--;
	}
	string k = s.substr(0,n_size);
	return k;
}
int hashFunc(string s){
	unsigned int value = 7951;
	for(int i = 0; i < s.length(); i++)
		value = value * 69 +s[i];
	return value % size;
}
struct place{
	string abb, name;
	int pop;
	double area, lat, lon;
	int cross;
	double distance;
};
place nah;

struct HashNode{
	int key;
	place data;
	HashNode * next;
	HashNode(int key, place data)
	{	this->key = key;
		this->data = data;
		this->next = NULL;	}
	int getKey()
	{	return key;	}
	place getPlace()
	{	return data;	}
	void setPlace(place data)
	{	this->data = data;	}
	HashNode * getNext()
	{	return next;		}
	void setNext(HashNode * next)
	{	this->next = next;		}
};
HashNode nope(0, nah);

struct HashMap{
	HashNode ** table;
	HashMap()
	{	table = new HashNode*[size];
		for(int i = 0; i < size; i++)
			table[i] = NULL;	}
	int printStates(int key, string s){
		int hash = (key % size);
		HashNode * temp = table[hash];
		if(temp == NULL){
			cout << "No such place\n";
			return -1;
		}
		int count = 0;
			while(temp != NULL){
				if(temp->data.name == s){
					count++;
					cout << temp->data.abb << ", ";
				}
				temp = temp->next;
			} 
		if(count == 0){
			cout << "No such place exists\n";
			return -1;
		}
		return 0;
	}
	place get(int key, string s)
	{	int hash = (key % size);
		if(table[hash] == NULL)
			return nah;
		else
		{	HashNode * temp = table[hash];
			while(temp != NULL && temp->data.abb != s)
				temp = temp->next;
			if(temp == NULL)
				return nah;
			else
				return temp->data;	}	
	}
	void put(int key, place entry){
		int hash = (key % size);
		HashNode * temp = table[hash];
		if(temp != NULL){
			while(temp->next != NULL)
				temp = temp->next;
			temp->next = new HashNode(key, entry);			
		}
		else {
			table[hash] = new HashNode(key, entry);  
		}
	}
};
HashMap readData(){
	HashMap map;
	fstream file("places.txt");	
	if (file.fail())
	{	cout << "Couldn't read file\n";
		exit(1);				
	}
	string line;
	char shit[10];
	string state = "  "; 
	string pname = "                               ";
	string population = "               ";
	string area = "          "; 
	string longitude = "           ";
	string latitude = "            ";
	string intersection = "        ";
	string distance = "          ";
	while(true){
		string line;
		char shit[10];
		string stat = "  ";
		string pname = "                                  ";
		string population = "            ";
		string area = "            ";
		string longitude = "                 ";
		string latitude = "                 ";
		string intersection = "          ";
		string distance = "           ";
		int i = 0;
		if(file.eof()) break;
		getline(file, line);
		int width = line.length();
		for(int i = 0; i < 8; i++)
			shit[i] = line[i]; 
		for(int i = 8; i < 10; i++)
			state[i-8] = line[i];
		int n = 10;
		i = 10;
		while(i < width){	
			pname[i-n] = line[i];
			if(line[i+1] == ' ' && line[i+2] == ' ')
				break;
			i++;
		} pname = trunc(pname);
		while(i < width){
			if(line[i] - '0' < 10 && line[i] - '0' >= 0)
				break;
			i++;
		}
		n = i; 
		while(i < width){
			population[i-n] = line[i];
			if(line[i+1] == ' ') break;
			i++;
		} population = trunc(population);
		while(i < width){ 
			if(line[i+1] - '0' < 10 && line[i+1] - '0' >= 0)
				break;
			i++;
		}
		i++;	
		n = i; 
		while(i < width){
			if(line[i] == ' ') break;
			area[i-n] = line[i];
			i++;
		}
		area = trunc(area); 
		while(i < width){
			if(line[i] != ' ') break;
			i++;
		}
		n = i;
		while(i < width){
			latitude[i-n] = line[i];			
			if(line[i+1] == ' ' || line[i+1] == '-') break;
			i++; 
		} i++;		
		latitude = trunc(latitude);
		while(i < width){ 
			if(line[i] != ' ') break;
			i++; 
		} n = i;
		while(i < width){
			longitude[i-n] = line[i];
			if(line[i-6] == '.') break;
			i++;
		} i++;
		longitude = trunc(longitude);
		while(i < width){
			if(line[i] != ' ') break;
			i++;
		} n = i;
		while(i < width){
			if(line[i] == ' ') break;
			intersection[i-n] = line[i];
			i++;
		}
		intersection = trunc(intersection);
		while(i < width){
			if(line[i] != ' ') break;
			i++;
		} n = i;
		while(i < width){
			distance[i-n] = line[i];
			i++;
		} distance = trunc(distance);
		
		place entry;
		entry.abb = state; entry.name = pname;
		entry.pop = str2int(population);
		entry.area = str2dub(area);
		entry.lat = str2dub(latitude);
		entry.lon = str2dub(longitude);
		entry.cross = str2int(intersection);
		entry.distance = str2dub(distance);		
	
		int key = hashFunc(entry.name);
//		cout << key << endl;
		map.put(key, entry); 
			
		/*	cout << state << " " << pname << " " << population << 
			" " << area << " " << latitude 
			<< " " << longitude << " " << intersection 
			<< " " << distance <<  endl; 			*/
	}
	return map;
 
}		



int main(){
	HashMap H; 
	H = readData();

while(true){
	string input;
	cout << "Enter a place name : ";
	getline(cin, input);
	int key = hashFunc(input);
	cout << "input: " << input << endl;
	int i = H.printStates(key, input);
	
	if(i == 0){
	string st;
	cin >> st;
	place ret;
	ret = H.get(key, st); 
	if(ret.area == NULL) {
		cout << "There is no " << input << " in " << st << endl;
	}
	else{
		cout << ret.name << ", " << ret.abb << endl;
		cout << "Population: " << ret.pop << endl;
		cout << "Area: " << ret.area << endl;
		cout << "Latitude: " << ret.lat << endl;
		cout << "Longitude: " << ret.lon << endl;
		cout << "Intersection: " << ret.cross << endl;
		cout << "Distance: " << ret.distance << endl;
	}
	}
}		
}

