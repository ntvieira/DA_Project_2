#ifndef PROGRAM2_H
#define PROGRAM2_H

#include "metrics.h"
#include <algorithm>

//Tom Vieira, 7/17/18

template <typename T>

bool comparePointByX(Point<T> left, Point<T> right){
    return left.x<right.x;
}

template <typename T>

bool comparePointByY(Point<T> left, Point<T> right){
    return left.y<right.y;
}

template <typename T>
std::pair<Point<T>, Point<T> > efficientClosestPair( vector<Point<T> > P, vector<Point<T> > Q){

    std::size_t n = P.size(); //n is the number of of points in v

    T dminsq;

    Point<T> best1(0,0);
    Point<T> best2(0,0);

    if (n<=3){
        return closestPairBF(P);
    }
    else{

        vector <Point<T> > Pl(ceil(n/2.0),Point<T>(0,0));
        vector <Point<T> > Ql(ceil(n/2.0),Point<T>(0,0));
        vector <Point<T> > Pr(n-ceil(n/2.0),Point<T>(0,0));
        vector <Point<T> > Qr(n-ceil(n/2.0),Point<T>(0,0));

        std::copy(P.begin(),P.begin()+ceil(n/2.0),Pl.begin());
        std::copy(Pl.begin(),Pl.end(),Ql.begin());
        std::sort(Ql.begin(),Ql.end(),comparePointByY<T>);

        std::copy(P.begin()+ceil(n/2.0), P.end(), Pr.begin());
        std::copy(Pr.begin(),Pr.end(),Qr.begin());
        std::sort(Qr.begin(),Qr.end(),comparePointByY<T>);

        std::pair<Point<T>, Point<T> > leftclosest = efficientClosestPair(Pl,Ql);

        std::pair<Point<T>, Point<T> > rightclosest = efficientClosestPair(Pr,Qr);


        T dl = dist(leftclosest.first,leftclosest.second);
        T dr = dist(rightclosest.first,rightclosest.second);

        T d = std::min(dl,dr);

        T m = P[ceil(n/2.0) - 1].x;

        vector <Point<T> > S;

        for(int i=0; i<Q.size();i++){
            if((abs(Q[i].x-m))<d){
                S.push_back(Q[i]);
            }
        }

        if(dl<dr){
            best1=leftclosest.first;
            best2=leftclosest.second;
        }else
                {
                    best1=rightclosest.first;
                    best2=rightclosest.second;
                }

        dminsq = d*d;

        int k=0;

        for(int i=0; i<=(int)S.size()-2; i++){

            k=i+1;

            while(k<=(int)S.size()-1 && (S[k].y-S[i].y)*(S[k].y-S[i].y)<dminsq){
                if ((S[k].x-S[i].x)*(S[k].x-S[i].x)+(S[k].y-S[i].y)*(S[k].y-S[i].y)< dminsq){

                    best1.x = S[k].x;
                    best2.x = S[i].x;

                    best1.y = S[k].y;
                    best2.y = S[i].y;
                }
                dminsq = std::min((S[k].x-S[i].x)*(S[k].x-S[i].x)+(S[k].y-S[i].y)*(S[k].y-S[i].y),dminsq);
                k = k+1;
            }
        }
    }

    return std::pair<Point<T>,Point<T> >(best1, best2);

}


template <typename T>
std::pair<Point<T>, Point<T> > closestPair( vector<Point<T> > v){


        vector <Point<T> > P(v);
        vector <Point<T> > Q(v);

        std::sort(P.begin(),P.end(),comparePointByX<T>);   //Sorting P by X
        std::sort(Q.begin(),Q.end(),comparePointByY<T>);   //Sorting Q by Y

    if(P.size()<=3){
        return closestPairBF(v);
    }

    return efficientClosestPair(P,Q);
 
}

#endif //PROGRAM2_H
