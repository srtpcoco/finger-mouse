#ifndef MATH_TOOLS
#define MATH_TOOLS
#include <algorithm> 
#include <math.h>
#include <vector>

class vector3D {
    public:
    float x_,y_,z_;
    // default con
    vector3D(): x_(0), y_(0),z_(0){}
    // copy constructor
    vector3D( const vector3D& other ):
                x_(other.x_),y_(other.y_),z_(other.z_){}
    // 3-parameter constructor
    vector3D( float x, float y, float z):
                x_(x),y_(y),z_(z){}
    vector3D( float a[3] ){
                x_ = a[0] ;
                y_ = a[1] ;
                z_ = a[2] ;
    }

    vector3D& operator()( float x, float y, float z){
        x_ = x;
        y_ = y;
        z_ = z;
        return *this;          
    }

    // overload =
    vector3D& operator = ( const vector3D& other ){
        x_ = other.x_ ,
        y_ = other.y_ ,
        z_ = other.z_ ;
        return *this;
    }

    // overload ==
    bool operator == ( const vector3D &other )const{
        return ( x_ ==other.x_ && y_== other.y_ && z_ == other.z_);
    }
    // overload != 
    bool operator != ( const vector3D &other )const{
        return ( x_ !=other.x_ || y_!= other.y_ || z_ != other.z_);
    }    

    // overload +
    vector3D operator +( const vector3D &other ) const{
        return vector3D( x_ + other.x_ , y_ + other.y_ , z_ + other.z_);
    }
    // overload -
    vector3D operator -( const vector3D &other ) const{
        return vector3D( x_ - other.x_ , y_ - other.y_ , z_ - other.z_);
    }

    // dot product
    float operator *(const vector3D &a) const {
        return x_*a.x_ + y_*a.y_ + z_*a.z_;
    }
    // cross product
    vector3D crossProduct(const vector3D &a, const vector3D &b) {
        return vector3D(a.y_*b.z_ - a.z_*b.y_ , 
                        a.z_*b.x_ - a.x_*b.z_ ,
                        a.x_*b.y_ - a.y_*b.x_ );
    }

};

class matirx3D{
    public:
    vector3D v1 , v2 , v3 ;

    matirx3D( float n1 , float n2 ,float n3 ,float n4 ,float n5 ,float n6 , float n7 , float n8 ,float n9 ){
        v1(n1 , n2 , n3); // first  line
        v2(n4 , n5 , n6); // second line
        v3(n7 , n8 , n9); // third  line
    }
    matirx3D ( vector3D v1_ , vector3D v2_ , vector3D v3_ ): v1(v1_), v2(v2_), v3(v3_){}
    matirx3D ( float row1[3], float row2[3], float row3[3] ){
        v1 = vector3D(row1);
        v2 = vector3D(row2);
        v3 = vector3D(row3);
    }
    
    // overload ==
    bool operator == ( const matirx3D &other )const{
        return ( v1 ==other.v1 && v2== other.v2 && v3 == other.v3 );
    }
    // overload != 
    bool operator != ( const matirx3D &other )const{
        return ( v1 !=other.v1 || v2!= other.v2 || v3 != other.v3);
    }    

    // overload +
    matirx3D operator +( const matirx3D &other ) const{
        return matirx3D( v1 + other.v1 , v2 + other.v2 , v3 + other.v3);
    }
    // overload -
    matirx3D operator -( const matirx3D &other ) const{
        return matirx3D( v1 - other.v1 , v2 - other.v2 , v3 - other.v3);
    }

    matirx3D transpose(){
        vector3D v1_( v1.x_ , v2.x_ , v3.x_ );
        vector3D v2_( v1.y_ , v2.y_ , v3.y_ );
        vector3D v3_( v1.z_ , v2.z_ , v3.z_ );
        return matirx3D( v1_ , v2_ , v3_ );
    }
    // product
    matirx3D product(  matirx3D first,  matirx3D second_){
        matirx3D second = second_.transpose();
        vector3D v1_( first.v1*second.v1, first.v1*second.v2 , first.v1*second.v3);
        vector3D v2_( first.v2*second.v1, first.v2*second.v2 , first.v2*second.v3);
        vector3D v3_( first.v3*second.v1, first.v3*second.v2 , first.v3*second.v3);
        return matirx3D( v1_, v2_, v3_);
    }

    void set( int row , int coln , float value){ // row 1 2 3 line 1 2 3
       vector3D* row_ ;
        switch ( row )
        {
        case 1:  row_ = &v1 ; break;
        case 2: row_ = &v2 ;break;
        case 3: row_ = &v3 ; break;
        }
         switch ( coln )
        {
        case 1: row_->x_ = value  ;break;
        case 2: row_->y_ = value  ;break;
        case 3: row_->z_ = value  ; break;
        }           
    }

};


/*
class quaternion{
private:
    float x_,y_,z_,w_;
    //vector<float> euler;
public:
    

    ~quaternion(){}

    quaternion(){
        x_=0;
        y_=0;
        z_=0;
        w_=1;
    }

    quaternion(float w,float x, float y,float z){
        float m=sqrt(x*x+y*y+z*z+w*w);
        x_=x/m;
        y_=y/m;
        z_=z/m;
        w_=w/m;
    }

    quaternion(float yaw, float pitch, float roll){
        this->euler_qua(yaw, pitch, roll);
    }

    void euler_qua(float yaw, float pitch, float roll){
        float yaw1,yaw2;
        float pitch1,pitch2;
        float roll1, roll2;

        yaw1=sin(yaw*0.5f);
        yaw2=cos(yaw*0.5f);
        pitch1=sin(pitch*0.5f);
        pitch2=cos(pitch*0.5f);
        roll1=sin(roll*0.5f);
        roll2=cos(roll*0.5f);

        float y = roll2*pitch1*yaw2 + roll1*pitch2*yaw1;	
        float x = roll2*pitch2*yaw1 - roll1*pitch1*yaw2;	
        float z = roll1*pitch2*yaw2 - roll2*pitch1*yaw1;	
        float w = roll2*pitch2*yaw2 + roll1*pitch1*yaw1;

        float m=sqrt(x*x+y*y+z*z+w*w);
        x_=x/m;
        y_=y/m;
        z_=z/m;
        w_=w/m;

    }

    std::vector<float> quat_euler(float w, float x, float y,float z){
        std::vector<float> euler;
        float yaw = atan2(2*(w*x + z*y), 1 - 2*(x*x + y*y));
        float pitch = asin(std::clamp(2*(w*y - x*z), -1.0f, 1.0f));	
        float roll = atan2(2*(w*z + x*y), 1 - 2*(z*z + y*y));
        euler.push_back(yaw);
        euler.push_back(pitch);
        euler.push_back(roll);
        return euler;  //??

    }

    void quaternion::operator+(const quaternion &q){
        x_=x_+q.x_;
        y_=y_+q.y_;
        z_=z_+q.z_;
        w_=w_+q.w_;
    }

    void quaternion::operator-(const quaternion &q){
        x_=x_-q.x_;
        y_=y_-q.y_;
        z_=z_-q.z_;
        w_=w_-q.w_;
    }

    void quaternion::operator=(const quaternion &q){
        x_=q.x_;
        y_=q.y_;
        z_=q.z_;
        w_=q.w_;
    }

};

*/
#endif