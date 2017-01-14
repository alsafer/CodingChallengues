#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>

using namespace std;

struct Path{
	set<int> positions;
	bool isLoop;
};

class Problem{
	vector<int> _values;
    Path _foundLoop{set<int>(), false};

	public:
		Problem(){};

		void readValues(string fileName){
            string line;
            ifstream file(fileName);

            if (file.is_open()){
                while ( getline (file,line) ) _values.push_back(stoi(line));
                file.close();
            }else
             cout << "Unable to open "<<fileName; 
		}

		bool isThereLoops(){
			vector<Path> paths;

			for(int currentPosition:_values){

				if(positionBelongsToAnotherPath(currentPosition,paths))
					continue;
				
				Path path = createPathFromPosition(currentPosition);

				if(path.isLoop){
                    _foundLoop = path;
					return true;
				}else
					paths.push_back(path);				

			}
			return false;
		}

        void printLoop(){
            if(_foundLoop.isLoop)
              for(auto t:_foundLoop.positions)
					  cout<<t<<" ";
        }

	private:

		Path createPathFromPosition(int startingPosition){
			Path path;
			int nextPosition,currentPosition = startingPosition;

			path.positions.insert(currentPosition);

			while(true){
			  nextPosition = (currentPosition+_values[currentPosition])%_values.size();
              bool positionAlreadyInPath = !path.positions.insert(nextPosition).second;
              
              if(positionAlreadyInPath)
                break;
			  
              currentPosition = nextPosition;
			};

			path.isLoop = nextPosition==currentPosition?false:true;

			return path;
		}

        bool positionBelongsToAnotherPath(int position,vector<Path>  paths){
            for(auto& path : paths){
                if(path.positions.find(position)!=path.positions.end())
                  return true;
            }
            return false;
        }

};

int main(int argc, char* argv[]){
	Problem p;

    if(argc<2){
      cout<<"Incorrect # of arguments"<<endl;
      exit(0);
    }

	p.readValues(argv[1]);

	if(p.isThereLoops()){
		cout<<"Loop!: ";
        p.printLoop();
        cout<<endl;
    }else
		cout<<"No loop!"<<endl;

	return 0;
}