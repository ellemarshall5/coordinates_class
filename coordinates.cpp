#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "coordinates.h"

using namespace std;

/**
 * @brief Construct a new point::Coordinates::Coordinates object
 *  Sets latitude and longitude to 0
 *
 */
Coordinates::Coordinates()
{
    set_latitude(0);
    set_longitude(0);
}

/**
 * @brief Construct a new point::Coordinates::Coordinates object
 * 
 * @param latitude: Initial Latitude
 * @param longitude: Initial Longitude
 */
Coordinates::Coordinates(float latitude, float longitude)
{
    set_latitude(latitude);
    set_longitude(longitude);
}

/**
 * @brief Setter for latitude
 * 
 * @param value, the value of the new latitude
 */
void Coordinates::set_latitude(float value)
{ 
    latitude_ = value; 
}

/**
 * @brief Set longitude for point
 * 
 * @param value, the value of the new longitude
 */
void Coordinates::set_longitude(float value)
{ 
    longitude_ = value; 
}
    

/**
 * @brief Get the latitude for the point
 * 
 * @return float, the value of latitude
 */
float Coordinates::latitude() const
{ 
    return latitude_; 
}

/**
 * @brief Get the longitude for the point
 * 
 * @return float, the value of longitude
 */
float Coordinates::longitude() const
{ 
    return longitude_; 
}

/**
 * @brief Convert latitude or longitude coordinates to 
 *  degrees, minutes, and seconds
 * 
 * 
 * @param number: latitude or longitude value
 * @param degrees: degrees int reference 
 * @param minutes: minutes int reference 
 * @param seconds: secods int reference 
 */
void Coordinates::from_float_to_gps_(float number, int &degrees, int &minutes, int &seconds)
{
    double frac = 0.0;
    //  * We will use the following formula to convert the units: 
    //  * 1) The whole units of degrees will remain the same (i.e. in 121.135° longitude, start with 121°).
    degrees = number; // take int part for degrees
    
    //  * 2) Multiply the decimal by 60 (i.e. .135 * 60 = 8.1).
    //  * 3) The whole number becomes the minutes (8′).
    frac = number - degrees;
    frac = fabs(frac * 60);
    minutes = frac; // take int part
    
    //  * 4) Take the remaining decimal and multiply by 60. (i.e. .1 * 60 = 6).
    //  * 5) The resulting number becomes the seconds (6″). Seconds can remain as a decimal.
    seconds = fabs(frac - minutes) * 60;
  
    //  * 6) Take your three sets of numbers and put them together, using the symbols for degrees (°), minutes (‘), and seconds (“) (i.e. 121°8’6” longitude)
    // cout<<"degrees: " << degrees << " minutes: " << minutes 
        // << " seconds: " << seconds << endl;
}

bool Coordinates::operator != (Coordinates c1) const{

    return (latitude_ != c1.latitude_ || longitude_ != c1.longitude_);

}

bool Coordinates::operator == (Coordinates c1) const{

    return (latitude_ == c1.latitude_ && longitude_ == c1.longitude_);

}

std::ostream &operator << (std::ostream &os, const Coordinates &c)
{
    os << std::fixed << setprecision(3) << "lat_: " << c.latitude_
    << " " << "long_: " << c.longitude_;
    return os;
}

std::string Coordinates::gps(){
    int degrees, minutes, seconds;
    from_float_to_gps_(latitude_, degrees, minutes, seconds);

    std::string gpsLatitude = to_string(degrees) + "\370" + to_string(minutes) + "\'"
            + to_string(seconds) + "\"";

    from_float_to_gps_(longitude_, degrees, minutes, seconds);

    std::string gpsLongitude = to_string(degrees) + "\370" + to_string(minutes) + "\'"
                              + to_string(seconds) + "\"";

    if (latitude_ >= 0){
        gpsLatitude = gpsLatitude + " N  ";
    }
    else{
        gpsLatitude = gpsLatitude.erase(0,1) + " S  ";
    }

    if(longitude_ < 0) {
        gpsLongitude = gpsLongitude.erase(0,1) + " W";
    }
    else{
        gpsLongitude = gpsLongitude + " E";
    }

    return gpsLatitude + gpsLongitude;
}



