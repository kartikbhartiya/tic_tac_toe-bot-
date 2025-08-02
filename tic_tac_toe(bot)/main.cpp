#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int first_time = 0;
char structure[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
int turns = 0;
int priority[8] = {1,1,1,1,1,1,1,1}; //D1 D2 R1 R2 R3 C1 C2 C3

class player{
public:
    char val;
    int row,column;
    void assign(char value){
        val = value;
    }
    void input(char structure[3][3]){
        int temp = 0;
        if(turns%2 == 0) cout<<"P1 turn:- ";
        else cout<<"P2 turn:- ";
        cin>>temp;
        column = temp%10 - 1;
        row = temp/10 - 1;
        if(structure[row][column] == '_'){ structure[row][column] = val; }//assigning the 'X' or 'O'
        else{
            cout<<"(Error) That Place is Already Occupied or Does Not Exist : Please Retry"<<endl;
            input(structure);
        }     
        cout<<endl;   
    }
    void display(char structure[3][3]){
        for(int i = 0 ; i<3 ; i++){
            for(int j = 0 ; j<3 ; j++){
                cout<<structure[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    int check(char structure[3][3]){
        if((structure[0][0] != '_' && structure[0][0] == val && structure[0][0] == structure[1][1] && structure[1][1] == structure[2][2]) || (structure[0][2] != '_' && structure[0][2] == val && structure[0][2] == structure[1][1] && structure[1][1] == structure[2][0])){ return 1;}
        else if((structure[0][0] != '_' && structure[0][0] == val && structure[0][0] == structure[0][1] && structure[0][1] == structure[0][2]) || (structure[1][0] != '_' && structure[1][0] == val && structure[1][0] == structure[1][1] && structure[1][1] == structure[1][2]) || (structure[2][0] != '_' && structure[2][0] == val && structure[2][0] == structure[2][1] && structure[2][1] == structure[2][2])){ return 1; }
        else if((structure[0][0] != '_' && structure[0][0] == val && structure[0][0] == structure[1][0] && structure[1][0] == structure[2][0]) || (structure[0][1] != '_' && structure[0][1] == val && structure[0][1] == structure[1][1] && structure[1][1] == structure[2][1]) || (structure[0][2] != '_' && structure[0][2] == val && structure[0][2] == structure[1][2] && structure[1][2] == structure[2][2])){ return 1; }
        return 0;
    }
    void ai_input(int a , int b){
        structure[a][b] = 'O';
        cout<<endl;
    }
int ai_defence(){ //To Check if The Player is about to win in one move
    // Check rows for 2 Xs and 1 _
    for(int i = 0; i < 3; i++){
        int x_count = 0, empty_j = -1;
        for(int j = 0; j < 3; j++){
            if(structure[i][j] == 'X') x_count++;
            else if(structure[i][j] == '_') empty_j = j;
        }
        if(x_count == 2 && empty_j != -1){
            ai_input(i, empty_j);
            return 0;
        }
    }

    // Check columns
    for(int j = 0; j < 3; j++){
        int x_count = 0, empty_i = -1;
        for(int i = 0; i < 3; i++){
            if(structure[i][j] == 'X') x_count++;
            else if(structure[i][j] == '_') empty_i = i;
        }
        if(x_count == 2 && empty_i != -1){
            ai_input(empty_i, j);
            return 0;
        }
    }

    // Check main diagonal
    int x_count = 0, empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][i] == 'X') x_count++;
        else if(structure[i][i] == '_') empty_idx = i;
    }
    if(x_count == 2 && empty_idx != -1){
        ai_input(empty_idx, empty_idx);
        return 0;
    }

    // Check anti-diagonal
    x_count = 0;
    empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][2-i] == 'X') x_count++;
        else if(structure[i][2-i] == '_') empty_idx = i;
    }
    if(x_count == 2 && empty_idx != -1){
        ai_input(empty_idx, 2-empty_idx);
        return 0;
    }
    return 1; //To check if ai_defence has already played the chance
}

int ai_attack(){ //check if an instant win is availaible
      // Check rows for 2 Xs and 1 _
    for(int i = 0; i < 3; i++){
        int x_count = 0, empty_j = -1;
        for(int j = 0; j < 3; j++){
            if(structure[i][j] == 'O') x_count++;
            else if(structure[i][j] == '_') empty_j = j;
        }
        if(x_count == 2 && empty_j != -1){
            ai_input(i, empty_j);
            return 0;
        }
    }

    // Check columns
    for(int j = 0; j < 3; j++){
        int x_count = 0, empty_i = -1;
        for(int i = 0; i < 3; i++){
            if(structure[i][j] == 'O') x_count++;
            else if(structure[i][j] == '_') empty_i = i;
        }
        if(x_count == 2 && empty_i != -1){
            ai_input(empty_i, j);
            return 0;
        }
    }

    // Check main diagonal
    int x_count = 0, empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][i] == 'O') x_count++;
        else if(structure[i][i] == '_') empty_idx = i;
    }
    if(x_count == 2 && empty_idx != -1){
        ai_input(empty_idx, empty_idx);
        return 0;
    }

    // Check anti-diagonal
    x_count = 0;
    empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][2-i] == 'O') x_count++;
        else if(structure[i][2-i] == '_') empty_idx = i;
    }
    if(x_count == 2 && empty_idx != -1){
        ai_input(empty_idx, 2-empty_idx);
        return 0;
    }
    return 1; //To check if ai_defence has already played the chance
}

void upd_priority(){ //makes an priority list moving in which line will be best move
        // Check rows for 2 Xs and 1 _
    for(int i = 0; i < 3; i++){
        if(priority[i+2] == 0) continue;
        int x_count = 0, empty_j = -1;
        for(int j = 0; j < 3; j++){
            if(structure[i][j] == 'O') priority[i+2]++;
            if(structure[i][j] == 'X') x_count++;
        }
        if(x_count >0){
            priority[i+2] = 0; //Updates The Priority to 0 since making a trio not possible
        }
    }

    // Check columns
    for(int j = 0; j < 3; j++){
        if(priority[j+5] == 0) continue;
        int x_count = 0, empty_i = -1;
        for(int i = 0; i < 3; i++){
            if(structure[i][j] == 'O') priority[j+5]++;
            if(structure[i][j] == 'X') x_count++;
        }
        if(x_count >0){
            priority[j+5] = 0;
        }
    }

    // Check main diagonal
    int x_count = 0, empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][i] == 'O') priority[0]++;
        if(structure[i][i] == 'X') x_count++;
    }
    if(x_count >0){
        priority[0] = 0;
    }

    // Check anti-diagonal
    x_count = 0;
    empty_idx = -1;
    for(int i = 0; i < 3; i++){
        if(structure[i][2-i] == 'O') priority[1]++;
        if(structure[i][2-i] == 'X') x_count++;
    }
    if(x_count >0){
        priority[1] = 0;
    }
    return;
}

void fall_back(){//Checks where to move next move if not in danger
    if(first_time == 0){
    first_time++;
    int r, c;
    do {
        r = rand() % 3;
        c = rand() % 3;
    } while (structure[r][c] != '_');
    ai_input(r, c);
    return;
    }
    int max = priority[0];
    int pos = 0;
    for(int i = 0 ; i<8 ; i++){
        if(max<priority[i]){
            max = priority[i];
            pos = i;
        }
    }
    if(pos == 0){
        for(int i = 0 ; i<3 ; i++){
            if(structure[i][i] == '_'){
                ai_input(i,i);
                break;
            }
        }
    }
    else if(pos == 1){
        for(int i = 0 ; i <3 ; i++){
            if(structure[i][2-i] == '_'){
                ai_input(i,2-i);
                break;
            }
        }
    }
    else if(pos>1 && pos<5){
        pos -= 2;
        for(int i = 2 ; i>=0 ; i--){
            if(structure[pos][i] == '_'){
                ai_input(pos,i);
                break;
            }
        }
    }
    else if(pos>4){
        pos-=5;
        for(int i = 0 ; i<3 ; i++){
            if(structure[i][pos] == '_'){
                ai_input(i,pos);
                break;
            }
        }
    }
}
};

int main(){
    srand(time(0));
    player p1;
    player p2;
    player ai;
    cout<<"(Input Format:- xy --> xth row and yth column)"<<endl;
    cout<<"(1) Human vs Human \n(2) Human vs Bot"<<endl;
    cout<<"Enter Your choice:- ";
    int choice = 0;
   cin>>choice;
    if(choice == 2){
    p1.assign('X');
    ai.assign('O');
    cout<<"_ _ _\n_ _ _\n_ _ _"<<endl;
    int temp = 0;int match = 0;
    int a1 = 0 , a2 = 0;
    while(temp!=9){
        if(turns%2 == 0){
            p1.input(structure);
            p1.display(structure);
            match = p1.check(structure);
            if(match == 1){
                cout<<"Player 1 Won!!\nPress Any Key to Continue... "<<endl;
                cin.ignore();
                cin.get();
                return 0;
            }
        }
        else{
            cout<<"\nThinking..."<<endl;
            a1 = ai.ai_attack();
            if(a1==1){
            a2 = ai.ai_defence();
            if(a2==1){
            ai.upd_priority();
            ai.fall_back();
            }
            }
            ai.display(structure);
            match = ai.check(structure);
            if(match == 1){
                cout<<"Bot Won!!\nPress Any Key to Continue... "<<endl;
                cin.ignore();
                cin.get();
                return 0;
            }
        }
        a1 = 0 , a2 = 0;
        temp++;
        turns++;
    }
    cout<<"No One Won!!\nPress Any Key to Continue... "<<endl;
    cin.ignore();
    cin.get();
}
else{
    p1.assign('X');
    p2.assign('O');
    cout<<"_ _ _\n_ _ _\n_ _ _"<<endl;
    int temp = 0;int match = 0;
    while(temp!=9){
        if(turns%2 == 0){
            p1.input(structure);
            p1.display(structure);
            match = p1.check(structure);
            if(match == 1){
                cout<<"Player 1 Won!!\nPress Any Key to Continue... "<<endl;
                cin.ignore();
                cin.get();
                return 0;
            }
        }
        else{
            p2.input(structure);
            p2.display(structure);
            match = p2.check(structure);
            if(match == 1){
                cout<<"Player 2 Won!!\nPress Any Key to Continue... "<<endl;
                cin.ignore();
                cin.get();
                return 0;
            }
        }
        temp++;
        turns++;
    }
    cout<<"No One Won!!\nPress Any Key to Continue... "<<endl;
    cin.ignore();
    cin.get();
    
}
    return 0;
}
