#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#include<set>
#include<deque>

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

class Excentricite{
    private:
        int n;  //dimension de la matrice
        Matrix A;
        int max_lengh;

    public:
        Matrix B;
        map<int,vector<int>>graph;
        Excentricite();
        ~Excentricite();
        void displayMatrix(Matrix M);
        void initializeData();
        void profil();
        void displayGraph();
        Matrix get_matrix();
        int min_path(int noeud,int dest);
};

Excentricite::Excentricite(){
    this->initializeData();
}

Excentricite::~Excentricite(){
    cout<<endl;
}

Matrix Excentricite::get_matrix(){
    return this->A;
}

void Excentricite::displayMatrix(Matrix M){
    for(int i=0;i<this->n;i++){
        for(int j=0;j<this->n;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Excentricite::initializeData(){
    ifstream file("data.txt");      //Ouvre le fichier data.txt

    if(file){
        file>>this->n;

        for(int i=0;i<this->n;i++){
            Vector temp;
            for(int j=0;j<this->n;j++){
                float element;
                file>>element;
                temp.push_back(element);
            }
            A.push_back(temp);
        }

        cout<<"Voici la matrice donnee :"<<endl;

        file.close();
    }

    else{
        cout<<"Erreur d'ouverture du fichier"<<endl;
    }
}

void Excentricite::profil(){
    for(int i=0;i<this->n;i++){
        for(int j=0;j<this->n;j++){
            if(A[i][j] != 0 && i != j){
                this->graph[i+1].push_back(j+1);
            }
        }
    }
}

void Excentricite::displayGraph(){
    for(int i=1;i<=this->n;i++){
        vector<int>& neighbor = this->graph[i];
        cout<<"Les voisins du noeud "<<i<<" : ";

        for(int n:neighbor){
            cout<<n<<" ";
        }
        cout<<endl;
    }
}

// int Excentricite::min_path(int noeud){
//     int e=0,i=0;
//     deque<int>f;
//     set<int>S;
//     f.push_back(noeud);
//     //Visiter le noeud
//     S.insert(noeud);
//     vector<int>N;
//     N.push_back(noeud);

//     while(!f.empty()){
//         int s = f.at(0);    //Accéder au premier élément
//         f.pop_front();      //Effacer le premier élément
//         vector<int>neighbors=this->graph[s];
//         if(S.size()==this->graph.size()){
//             break;
//         }

//         for(int neighbor:neighbors){
//             if(S.insert(neighbor).second){
//                 f.push_back(neighbor);
//                 S.insert(neighbor);
//             }
//             N.push_back(neighbor);
//         }
//     }
//     return e;
// }

int Excentricite::min_path(int noeud,int dest){
    deque<map<int,vector<int>>>file;
    set<int> visited;
    map<int,vector<int>> t;
    t[noeud].push_back(noeud);
    file.push_back(t);
    //Visiter le noeud
    visited.insert(noeud);
    vector<int>N;

    while(!file.empty()){
        map<int,vector<int>> queue = file.front();    //Accéder au premier élément
        file.pop_front();
        vector<int>path;
        int noeud = 0;
        for(auto s:queue){
            noeud = s.first;
            path = s.second;
        }
        
        if(noeud==dest){
            return path.size()-1;
        }
        vector<int>neighbors = this->graph[noeud];

        for(auto neighbor:neighbors){
            if(visited.insert(neighbor).second){
                map<int,vector<int>> next;
                next[neighbor].push_back(neighbor);
                for(auto pt:path){
                    next[neighbor].push_back(pt);
                }
                file.push_back(next);
            }
        }
    }

    return 0;
}




int main(){
    Excentricite a;
    a.displayMatrix(a.get_matrix());
    a.profil();
    a.displayGraph();
    
    for(int i=1;i<=a.graph.size();i++){
        //cout <<"Excentricite de "<< i << " vaut "<< a.min_path(i) << endl;
        cout <<"\nDistance entre \n"<<"2  et "<< i << " : "<< a.min_path(2,i) << endl;
    }
    

    return(0);
}
