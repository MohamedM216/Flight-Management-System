#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <map>
#include "json.hpp"

using namespace std;
using namespace json;

/////////////// Helper Methods ///////////////////

int ReadChoice(int lower, int higher) {
    cout << "Enter choice between " << lower << " - " << higher << ": ";
    int choice;
    cin >> choice;

    if (lower <= choice && choice <= higher)
        return choice;

    cout << "ERROR: invalid number...Try again\n";
    return ReadChoice(lower, higher);
}

int ShowMenu(const vector<string>& choices) {
    cout << "\n\tMenu:\n";
    for (int ch = 0; ch < (int)choices.size(); ++ch)
        cout << "\t\t" << ch + 1 << ": " << choices[ch] << ".\n";
    return ReadChoice(1, choices.size());
}

/////////////////// APIs ////////////////////////

////////////////////// Flight APIs /////////////////////////
class AirCanadaCustomerInfo
{
};

class AirCanadaFlight
{
public:
    double price;
    string date_time_from;
    string date_time_to;
};

class AirCanadaOnlineAPI
{
public:
    static vector<AirCanadaFlight> GetFlights(string from, string from_date, string to, string to_date, int adults, int childern)
    {
        vector<AirCanadaFlight> flights;

        flights.push_back({200, "25-01-2022", "10-02-2022"});
        flights.push_back({250, "29-01-2022", "10-02-2022"});
        return flights;
    }
    static bool ReserveFlight(const AirCanadaFlight &flight, const AirCanadaCustomerInfo &info)
    {
        return true;
    }
};

class TurkishFlight
{
public:
    double cost;
    string datetime_from;
    string datetime_to;
};

class TurkishCustomerInfo
{
};

class TurkishAirlinesOnlineAPI
{
public:
    void SetFromToInfo(string datetime_from, string from, string datetime_to, string to)
    {
    }
    void SetPassengersInfo(int infants, int childern, int adults)
    {
    }
    vector<TurkishFlight> GetAvailableFlights() const
    {
        vector<TurkishFlight> flights;

        flights.push_back({300, "10-01-2022", "10-02-2022"});
        flights.push_back({320, "12-01-2022", "10-02-2022"});
        return flights;
    }

    static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight &flight)
    {
        return false;
    }
};

////////////////////////// Hotel APIs ////////////////////////////////////

class HiltonRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI {
public:
	static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
		vector<HiltonRoom> rooms;

		rooms.push_back( { "Interior View", 6, 200.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "City View", 3, 300.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Deluxe View", 8, 500.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

class MarriottFoundRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI {
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
		vector<MarriottFoundRoom> rooms;

		rooms.push_back( { "City View", 8, 320.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Interior View", 8, 220.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Private View", 5, 600.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

//////////////////////// Payment APIs ///////////////////////////

class PayPalCreditCard {
public:
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	string name;
	string address;
};

class StripeCardInfo {
public:
	string id;
	string expiry_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
		return true;
	}
};

class SquarePaymentAPI {
public:
	bool static WithDrawMoney(string JsonQuery) {
		//cout << JsonQuery << "\n";
		json::JSON obj = JSON::Load(JsonQuery);
		return true;
	}
};
///////////////////////////////////////////////////////////////






class API
{
public:
    virtual string GetClassName() const = 0;
    virtual ~API()
    {
    }
};



class ReservationAPI : public API
{
public:
    virtual vector<double> GetCost() = 0;
    virtual ~ReservationAPI()
    {
    }
};

class PaymentAPI : public API
{
public:
    virtual void SetUserInfo(string name, string address) = 0;
    virtual void SetCardInfo(string name, string address, string id, string expiry_date, int ccv) = 0;
    virtual bool MakePayment(double money) = 0;
    virtual ~PaymentAPI()
    {
    }
};



class FlightAPI : public ReservationAPI
{
public:
    virtual bool SetUserInfo(int adults, int children, int infants) = 0;
    virtual void SetFlightInfo(string from_date, string to_date, double cost) = 0;
    virtual bool ReserveFlight() = 0;
    virtual vector<string> GetAirlineInfo() = 0;
    
    virtual ~FlightAPI()
    {
    }
};

class HotelAPI : public ReservationAPI
{
public:
    virtual bool SetHotelInfo() = 0;
    virtual vector<string> GetHotelRoomsInfo() = 0;
    virtual ~HotelAPI()
    {
    }
};



class AirCanadaAPI : public FlightAPI
{
private:
    AirCanadaCustomerInfo user;
    AirCanadaFlight flight;

public:
    virtual string GetClassName() const override {
        return "AirCanada Airlines";
    }

    virtual bool SetUserInfo(int adults, int children, int infants) override {
        return true;
    }

    virtual void SetFlightInfo(string from_date, string to_date, double cost) override
    {
        flight.date_time_from = from_date;
        flight.date_time_to = to_date;
        flight.price = cost;
    }

    virtual bool ReserveFlight() override
    {
        return AirCanadaOnlineAPI::ReserveFlight(flight, user);
    }

    vector<AirCanadaFlight> GetAvailableFlights()
    {
        return AirCanadaOnlineAPI::GetFlights("", flight.date_time_from, "", flight.date_time_to, 0, 0);
    }

    // info of the airline
    virtual vector<string> GetAirlineInfo() override {
        vector<AirCanadaFlight> vec = GetAvailableFlights();
        vector<string> result;

        for (int fl = 0; fl < (int) vec.size(); ++fl) {
            ostringstream oss;
            oss << GetClassName() << " Cost: " << vec[fl].price << " Departure Date " << vec[fl].date_time_from << " Arrival Date " << vec[fl].date_time_to;
            result.push_back(oss.str());
        }
        return result;
    }

    virtual vector<double> GetCost() override {
        vector<AirCanadaFlight> vec = GetAvailableFlights();
        vector<double> result;
        for (int fl = 0; fl < (int) vec.size(); ++fl) {
            result.push_back(vec[fl].price);
        }
        return result;
    }
};

class AirTurkishAPI : public FlightAPI
{
private:
    TurkishCustomerInfo user;
    TurkishFlight flight;
    TurkishAirlinesOnlineAPI turkish_online_api;
public:
    string GetClassName() const override {
        return "AirTurkish Airlines";
    }    

    virtual bool SetUserInfo(int adults, int children, int infants) override {
        return true;
    }

    virtual void SetFlightInfo(string from_date, string to_date, double cost) override {
        flight.datetime_from = from_date;
        flight.datetime_to = to_date;
        flight.cost = cost;
    }

    virtual bool ReserveFlight() override {
        turkish_online_api.SetFromToInfo(flight.datetime_from, "", flight.datetime_to, "");
        turkish_online_api.SetPassengersInfo(0, 0 , 0);
        return TurkishAirlinesOnlineAPI::ReserveFlight(user, flight);
    }

    vector<TurkishFlight> GetAvailableFlights() const {
        return turkish_online_api.GetAvailableFlights();
    }

    // info of the airline
    virtual vector<string> GetAirlineInfo() override {
        vector<TurkishFlight> vec = GetAvailableFlights();
        vector<string> result;

        for (int fl = 0; fl < (int) vec.size(); ++fl) {
            ostringstream oss;
            oss << GetClassName() << " Cost: " << vec[fl].cost << " Departure Date " << vec[fl].datetime_from << " Arrival Date " << vec[fl].datetime_to;
            result.push_back(oss.str());
        }
        return result;
    }

    virtual vector<double> GetCost() override{
        vector<TurkishFlight> vec = GetAvailableFlights();
        vector<double> result;
        for (int fl = 0; fl < (int) vec.size(); ++fl) {
            result.push_back(vec[fl].cost);
        }
        return result;
    }
};



class MyHiltonHotelAPI : public HotelAPI {
private:
    HiltonHotelAPI hilton_hotil_api;

public:
    virtual string GetClassName() const override {
        return "Helton Hotel";
    }

    virtual bool SetHotelInfo() override {
        return true;
    }

    virtual vector<string> GetHotelRoomsInfo() override {
        vector<HiltonRoom> rooms = HiltonHotelAPI::SearchRooms("", "", "", "", 0, 0, 0);
        vector<string> result;

        for (int r = 0; r < (int) rooms.size(); ++r) {
            ostringstream oss;
            oss << GetClassName() << " Room Type: " << rooms[r].room_type << "(" << rooms[r].available << ") Price per night: " << rooms[r].price_per_night << " From Date " << rooms[r].date_from << " To " << rooms[r].date_to;
            result.push_back(oss.str());
        }
        return result;
    }

    virtual vector<double> GetCost() override {
        vector<HiltonRoom> rooms = HiltonHotelAPI::SearchRooms("", "", "", "", 0, 0, 0);
        vector<double> result;

        for (int r = 0; r < (int) rooms.size(); ++r) {
            result.push_back(rooms[r].price_per_night);
        }
        return result;        
    }
};

class MyMarriottHotelAPI : public HotelAPI {
private:
    MarriottHotelAPI marriott_hotel_api;

public:

    virtual string GetClassName() const override {
        return "Marriott Hotel";
    }

    virtual bool SetHotelInfo() override {
        return true;
    }

    virtual vector<string> GetHotelRoomsInfo() override {
        vector<MarriottFoundRoom> rooms = MarriottHotelAPI::FindRooms("", "", "", "", 0, 0, 0);
        vector<string> result;

        for (int r = 0; r < (int) rooms.size(); ++r) {
            ostringstream oss;
            oss << GetClassName() << " Room Type: " << rooms[r].room_type << "(" << rooms[r].available << ") Price per night: " << rooms[r].price_per_night << " From Date " << rooms[r].date_from << " To " << rooms[r].date_to;
            result.push_back(oss.str());
        }
        return result;
    }

    virtual vector<double> GetCost() override {
        vector<MarriottFoundRoom> rooms = MarriottHotelAPI::FindRooms("", "", "", "", 0, 0, 0);
        vector<double> result;

        for (int r = 0; r < (int) rooms.size(); ++r) {
            result.push_back(rooms[r].price_per_night);
        }
        return result;        
    }    
};
  


class PaypalAPI : public PaymentAPI {
private:
    PayPalCreditCard card;
    PayPalOnlinePaymentAPI paypal_api;

public:
    virtual void SetCardInfo(string name, string address, string id, string expiry_date, int ccv) {
        card.name = name;
        card.address = address;
        card.id = id;
        card.expiry_date = expiry_date;
        card.ccv = ccv;
        paypal_api.SetCardInfo(&card);
    }

    virtual bool MakePayment(double money) {
        paypal_api.SetCardInfo(&card);
        return paypal_api.MakePayment(money);
    }
};

class StripeAPI : public PaymentAPI {
private:
    StripeCardInfo card;
    StripeUserInfo user;

public:
    virtual void SetUserInfo(string name, string address) {
        user.name = name;
        user.address = address;
    }

    virtual void SetCardInfo(string id, string expiry_date) {
        card.id = id;
        card.expiry_date = expiry_date;
    }

    virtual bool MakePayment(double money) {

        return StripePaymentAPI::WithDrawMoney(user, card, money);
    }
};

class SquareAPI : public PaymentAPI {
private:
    string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
public:
    virtual void SetUserInfo(string name_, string address_) {
		name = name_;
		address = address_;
	}

	virtual void SetCardInfo(string id_, string expiry_date_, int ccv_) {
		id = id_;
		expiry_date = expiry_date_;
		ccv = ccv_;
	}

    virtual bool MakePayment(double money) {
        json::JSON obj;
        obj["user_info"] = json::Array(name, address);
        obj["card_info"] = id;
        obj["card_info"] = expiry_date;
        obj["card_info"] = ccv;
        obj["money"] = money;

        ostringstream oss;
        oss << obj;
        string json_query = oss.str();

        return SquarePaymentAPI::WithDrawMoney(json_query);
    }
};


///////////////////////// APIs Factory //////////////////////////////

class APIsFactory
{
private:
    int choice;
    vector<ReservationAPI*> requested_apis;
    
public:
    APIsFactory(int choice) : choice(choice) {
        if (choice == 1) {
            requested_apis.push_back(new AirCanadaAPI());
            requested_apis.push_back(new AirTurkishAPI());
        } else if (choice == 2) {
            requested_apis.push_back(new MyHiltonHotelAPI());
            requested_apis.push_back(new MyMarriottHotelAPI());
        }
    }

    ~APIsFactory() {
        Clear();
        cout << "\nDestroy APIsFactory\n";
    }

    void Clear() {
        for (ReservationAPI* api : requested_apis) {
            delete api;
            api = nullptr;
        }
        requested_apis.clear();
    }

    const vector<ReservationAPI*>& GetAPIs() const {
        return requested_apis;
    }

};

////////////////// APIs Ends ///////////////////
////////////////////////////////////////////////

class Reservation
{
public:
    virtual bool MakeReservation(vector<Reservation *>& temp_reservations) = 0;
    virtual double TotalCost() const = 0;
    virtual void print() = 0;
    virtual ~Reservation()
    {
    }
};

class FlightReservation : public Reservation
{
private:
    static const int API_TYPE = 1;
    string from;
    string from_date;
    string to;
    string to_date;
    string flight_api_name;
    double cost { };
    int number_of_adults{};
    int number_of_children{};
    int number_of_infants{};

public:
    // Constructor
    FlightReservation() {
        cout << "FlightReservation Constructor\n";
    }
    // Destructor
    ~FlightReservation() {
        cout << "FlightReservation Destructor\n";
    }

    // Getters
    const string &GetFrom() const
    {
        return from;
    }

    const string &GetFromDate() const
    {
        return from_date;
    }

    const string &GetTo() const
    {
        return to;
    }

    const string &GetToDate() const
    {
        return to_date;
    }

    const int &GetNumberOfAdults() const
    {
        return number_of_adults;
    }

    const int &GetNumberOfChildren() const
    {
        return number_of_children;
    }

    const int &GetNumberOfInfants() const
    {
        return number_of_infants;
    }

    const double& GetCost() const {
        return cost;
    }

    const string& GetFlightAPIName() const {
        return flight_api_name;
    }
    // Getters End

    // Setters
    void SetFrom(const string &from)
    {
        this->from = from;
    }

    void SetFromDate(const string &from_date)
    {
        this->from_date = from_date;
    }

    void SetTo(const string &to)
    {
        this->to = to;
    }

    void SetToDate(const string &to_date)
    {
        this->to_date = to_date;
    }

    void SetNumberOfAdults(int number_of_adults)
    {
        this->number_of_adults = number_of_adults;
    }

    void SetNumberOfChildren(int number_of_children)
    {
        this->number_of_children = number_of_children;
    }

    void SetNumberOfInfants(int number_of_infants)
    {
        this->number_of_infants = number_of_infants;
    }

    void SetCost(double cost) {
        this->cost = cost;
    }

    void SetFlightAPIName(const string& flight_api_name) {
        this->flight_api_name = flight_api_name;
    }
    // Setters End

    void Read()
    {
        string str;
        int num{};

        cout << "Enter from: ";
        cin >> str;
        SetFrom(str); 
        
        cout << "Enter from_date: ";
        cin >> str;
        SetFromDate(str);

        cout << "Enter to: ";
        cin >> str;
        SetTo(str);

        cout << "Enter to_date: ";
        cin >> str;
        SetToDate(str);

        cout << "Enter number of adults (more than 13 years old): ";
        cin >> num;
        SetNumberOfAdults(num);

        cout << "Enter number of children (between 6 and 13 years old): ";
        cin >> num;
        SetNumberOfChildren(num);
    }

    pair<int, int> FindFlightAPI(vector<FlightAPI*>& flight_apis, int choice, int api_counter = 0, int choosen_flight = 1) {
        for (int api = 0; api < (int) flight_apis.size(); ++api) {
            vector<string> airlines = flight_apis[api]->GetAirlineInfo();

            for (int fl = 0; fl < (int) airlines.size(); ++fl) {
                if (choosen_flight == choice) {
                    return make_pair(api, fl);
                }
                ++choosen_flight;
            }
        }
        return make_pair(0, 0);
    }

    virtual bool MakeReservation(vector<Reservation *>& temp_reservations) override
    {
        // Read
        // Fill FlightReservation object with info
        // Call APIs
        // choose which one or cancel
        // if not cancel, send info to that API
        // use the object and API class name in a temp map
        // then send true

        FlightReservation* new_flight = new FlightReservation();
        new_flight->Read();

        APIsFactory* factory = new APIsFactory(API_TYPE);
        vector<FlightAPI*> flight_apis;

        for (ReservationAPI* r_api : factory->GetAPIs()) {
            if (dynamic_cast<FlightAPI*>(r_api))
                flight_apis.push_back(dynamic_cast<FlightAPI*>(r_api));
        }

        int higher = 0;
        for (int api = 0; api < (int) flight_apis.size(); ++api) {
            vector<string> airlines = flight_apis[api]->GetAirlineInfo();
            higher += (int) airlines.size();

            for (int fl = 0; fl < (int) airlines.size(); ++fl)
                cout << "Airline: " << airlines[fl] << "\n";
        }

        int choice = ReadChoice(1, higher);

        int api_counter = 0, choosen_flight = 1;
        pair<int, int> mypair = FindFlightAPI(flight_apis, choice, api_counter, choosen_flight);

        flight_apis[mypair.first]->ReserveFlight();   // Send info to the API
        new_flight->SetFlightAPIName(flight_apis[mypair.first]->GetClassName());
        new_flight->SetCost(flight_apis[mypair.first]->GetCost()[mypair.second]);
        temp_reservations.push_back(new_flight);

        if (factory != nullptr) {
            delete factory;
            factory = nullptr;
        }
        return true;
    }

    virtual double TotalCost() const override {
        return GetCost();
    }

    virtual void print() override {
        cout << "Airline reservation with reservation: ";
        cout << GetFlightAPIName() << ": \n";
        cout << "\t From " << GetFrom() << " On " << GetFromDate() << "\n";
        cout << "\t To " << GetTo() << " On " << GetToDate() << "\n";
        cout << "\t Adults: " << GetNumberOfAdults() << " Children: " << GetNumberOfChildren() << " Infants: " << GetNumberOfInfants() << "\n";
        cout << "\t Total cost: " << TotalCost() << "\n";
    }
};

class HotelReservation : public Reservation
{
private:
    static const int API_TYPE = 2;
    string from_date;
    string to_date;
    string country;
    string city;
    string hotel_api_name;
    double cost_per_night{};
    int number_of_adults{};
    int number_of_children{};
    int number_of_infants{};

public:
    // Constructor
    HotelReservation() {
        cout << "HotelReservation Constructor\n";
    }

    // Destructor
    ~HotelReservation() {
        cout << "HotelReservation Destructor\n";
    }

    // Setters
    void SetFromDate(const string &from_date)
    {
        this->from_date = from_date;
    }

    void SetToDate(const string &to_date)
    {
        this->to_date = to_date;
    }

    void SetCountry(const string &country)
    {
        this->country = country;
    }

    void SetCity(const string &city)
    {
        this->city = city;
    }

    void SetHotelAPIName(const string& hotel_api_name) {
        this->hotel_api_name = hotel_api_name;
    }

    void SetCostPerNight(double cost_per_night) {
        this->cost_per_night = cost_per_night;
    }

    void SetNumberOfAdults(int number_of_adults)
    {
        this->number_of_adults = number_of_adults;
    }

    void SetNumberOfChildren(int number_of_children)
    {
        this->number_of_children = number_of_children;
    }

    void SetNumberOfInfants(int number_of_infants)
    {
        this->number_of_infants = number_of_infants;
    }

    // Setters End

    // Getters
    const string &GetFromDate() const
    {
        return from_date;
    }

    const string &GetToDate() const
    {
        return to_date;
    }

    const string &GetCountry() const
    {
        return country;
    }

    const string &GetCity() const
    {
        return city;
    }

    const string& GetHotelAPIName() const {
        return hotel_api_name;
    }

    double GetCostPerNight() const {
        return cost_per_night;
    }

    int GetNumberOfAdults() const
    {
        return number_of_adults;
    }

    int GetNumberOfChildren() const
    {
        return number_of_children;
    }

    int GetNumberOfInfants() const
    {
        return number_of_infants;
    }
    // Getters End

    virtual double TotalCost() const override {
        // We need to count nights, but no problem for now as it is just dummy data
        return GetCostPerNight() * GetNumberOfAdults();
    }

    pair<int, int> FindHotelAPI(vector<HotelAPI*>& hotel_apis, int choice, int api_counter = 0, int choosen_room = 1) {
        for (int api = 0; api < (int) hotel_apis.size(); ++api) {
            vector<string> hotels = hotel_apis[api]->GetHotelRoomsInfo();

            for (int r = 0; r < (int) hotels.size(); ++r) {
                if (choosen_room == choice) {
                    return make_pair(api, r);
                }
                ++choosen_room;
            }
        }
        return make_pair(0, 0);
    }

    // Read
    void Read()
    {
        string str;
        int num{};

        cout << "Enter from_date: ";
        cin >> str;
        SetFromDate(str);

        cout << "Enter to_date: ";
        cin >> str;
        SetToDate(str);

        cout << "Enter country: ";
        cin >> str;
        SetCountry(str);
        
        cout << "Enter city: ";
        cin >> str;
        SetCity(str);
        
        cout << "Enter number of adults (more than 13 years old): ";
        cin >> num;
        SetNumberOfAdults(num);

        cout << "Enter number of children (between 6 and 13 years old): ";
        cin >> num;
        SetNumberOfChildren(num);
    }

    // MakeReservation
    virtual bool MakeReservation(vector<Reservation *>& temp_reservations) override
    {
        // Read
        // Fill FlightReservation object with info
        // Call APIs
        // choose which one or cancel
        // if not cancel, send info to that API
        // use the object and API class name in a temp map
        // then send true

        HotelReservation* new_hotel = new HotelReservation();
        new_hotel->Read();

        APIsFactory* factory = new APIsFactory(API_TYPE);
        vector<HotelAPI*> hotel_apis;
        for (ReservationAPI* r_api : factory->GetAPIs()) {
            if (dynamic_cast<HotelAPI*>(r_api))
                hotel_apis.push_back(dynamic_cast<HotelAPI*>(r_api));
        }

        int higher = 0;
        for (int api = 0; api < (int) hotel_apis.size(); ++api) {
            vector<string> hotels = hotel_apis[api]->GetHotelRoomsInfo();
            higher += (int) hotels.size();

            for (int fl = 0; fl < (int) hotels.size(); ++fl)
                cout << "Hotel: " << hotels[fl] << "\n";
        }

        int choice = ReadChoice(1, higher);

        int api_counter = 0, choosen_room = 1;
        pair<int, int> mypair = FindHotelAPI(hotel_apis, choice, api_counter, choosen_room);

        hotel_apis[mypair.first]->SetHotelInfo();   // Send info to the API
        new_hotel->SetHotelAPIName(hotel_apis[mypair.first]->GetClassName());
        new_hotel->SetCostPerNight(hotel_apis[mypair.first]->GetCost()[mypair.second]);
        temp_reservations.push_back(new_hotel);

        if (factory != nullptr) {
            delete factory;
            factory = nullptr;
        }
        return true;
    }

    virtual void print() override {
        cout << "Hotel reservation: ";
        cout << GetHotelAPIName() << ": \n";
        cout << "\t " << GetCity() << " @ " << GetCountry() << "\n";
        cout << "\t From " << GetFromDate() << " To " << GetToDate() << "\n";
        cout << "\t Adults: " << GetNumberOfAdults() << " Children: " << GetNumberOfChildren() << " Infants: " << GetNumberOfInfants() << "\n";
        cout << "\t Total cost: " << TotalCost() << "\n";
    }
    
};


class Card {
public:
    virtual string GetCardType() const = 0;
    virtual string ToString() = 0;

    virtual void SetName(const string& name) = 0;
    virtual void SetAddress(const string& address) = 0;
    virtual void SetId(const string& id) = 0;
    virtual void SetExpiryDate(const string& ex_date) = 0;
    virtual void SetCCV(int ccv) = 0;

    virtual const string& GetName() const = 0;
    virtual const string& GetAddress() const = 0;
    virtual const string& GetId() const = 0;
    virtual const string& GetExpiryDate() const = 0;
    virtual int GetCCV() const = 0;

    virtual ~Card() {

    }
};

class CreditCard : public Card {
private:
    string name;
	string address;
	string id;
	string expiry_date;
	int ccv;

public:
    virtual string GetCardType() const {
        return "Credit Card";
    }

    virtual void SetName(const string& name) {
        this->name = name;
    }

    virtual void SetAddress(const string& address) {
        this->address = address;
    }

    virtual void SetId(const string& id) {
        this->id = id;
    }

    virtual void SetExpiryDate(const string& ex_date) {
        this->expiry_date = expiry_date;
    }

    virtual void SetCCV(int ccv) {
        this->ccv = ccv;
    }

    virtual const string& GetName() const {
        return name;
    }

    virtual const string& GetAddress() const {
        return address;
    }

    virtual const string& GetId() const {
        return id;
    }
    virtual const string& GetExpiryDate() const {
        return expiry_date;
    }

    virtual int GetCCV() const {
        return ccv;
    }

    virtual string ToString() {
        ostringstream oss;
        oss << "[" << GetCardType() << "] Owner: " << GetName() << " Card Number: " << GetId();
        return oss.str();
    }

};

class DebitCard : public Card {
private:
    string name;
	string address;
	string id;
	string expiry_date;
	int ccv;

public:
    virtual string GetCardType() const {
        return "Debit Card";
    }

    virtual void SetName(const string& name) {
        this->name = name;
    }

    virtual void SetAddress(const string& address) {
        this->address = address;
    }

    virtual void SetId(const string& id) {
        this->id = id;
    }

    virtual void SetExpiryDate(const string& ex_date) {
        this->expiry_date = expiry_date;
    }

    virtual void SetCCV(int ccv) {
        this->ccv = ccv;
    }

    virtual const string& GetName() const {
        return name;
    }

    virtual const string& GetAddress() const {
        return address;
    }

    virtual const string& GetId() const {
        return id;
    }
    virtual const string& GetExpiryDate() const {
        return expiry_date;
    }

    virtual int GetCCV() const {
        return ccv;
    }

    virtual string ToString() {
        ostringstream oss;
        oss << "[" << GetCardType() << "] Owner: " << GetName() << " Card Number: " << GetId();
        return oss.str();
    }
};
//////////////////////////////////////////////////////////////

class Itinerary 
{
private:
    Card* card;
    PaymentAPI* payment_api;
    vector<Reservation*> reservations;

public:
    // Constructor
    Itinerary() {
        cout << "Itinerary Constructor\n";
    }

    // Destructor
    ~Itinerary() {
        // Clear();
        cout << "Itinerary Destructor\n";
    }

    void Clear() {
        for (Reservation* r : reservations) {
            delete r;
        }
        reservations.clear();
        delete card;
        delete payment_api;
    }

    // Getters
    const vector<Reservation*>& GetReservationsVector() {
        return this->reservations;
    }

    int GetReservationsCount() const {
        return (int) reservations.size();
    }
    // Getters End

    // Setters
    void SetReservationsVector(vector<Reservation*>& temp_reservations) {
        reservations = temp_reservations;
    }
    // Setters End

    double TotalCost() const {
        double total { };
        for (Reservation* reservation : reservations)
            total += reservation->TotalCost();
        return total;
    }

    

    bool MakeItineraryReservations(Itinerary& it)
    {   
        vector<Reservation*> temp_reservations;
        vector<string> menu;
        menu.push_back("Add Flight");
        menu.push_back("Add Hotel");
        menu.push_back("Done");
        menu.push_back("Cancel");
        
        while (true) {
            int choice = ShowMenu(menu);

            if (choice == 1) {
                FlightReservation* new_flight = new FlightReservation();
                new_flight->MakeReservation(temp_reservations);

                if (new_flight != nullptr) {
                    delete new_flight;
                    new_flight = nullptr;
                }

            } else if (choice == 2) {
                HotelReservation* new_hotel = new HotelReservation();
                new_hotel->MakeReservation(temp_reservations);

                if (new_hotel != nullptr) {
                    delete new_hotel;
                    new_hotel = nullptr;
                }

            } else if (choice == 3) {   // DONE

                break;
            } else {                    // CANCEL
                assert(it.CancelReservation(temp_reservations));
                return false;
            }
        }
        it.SetReservationsVector(temp_reservations);
        return true;
    }

    bool CancelReservation(vector<Reservation*>& temp_reservations) {
        for (Reservation* reservation : temp_reservations) {
            delete reservation;
            reservation = nullptr;
        }
        temp_reservations.clear();
        return true;
    }

    void print() {
        cout << "______________________________________________\n";
        cout << "Itinerary of " << GetReservationsCount() << " sub-reservations:\n";
        if (!(GetReservationsCount() > 0))
            return;

        for (int r = 0; r < GetReservationsCount(); ++r) {
            if (reservations[r] == nullptr)
                continue;
            reservations[r]->print();
        }
        
        cout << "\n\nTotal Itinerary Cost: " << TotalCost() << "\n";
        cout << "______________________________________________\n";
    }

};



class User {
private:
    string user_name;
	string password;
	string name;
	string email;

    vector<Itinerary> itineraries;
    vector<Card*> cards;

public:
    User(const User&) = delete;
    void operator=(const User&) = delete;

    User() {
        cout << "User Constructor\n";
    }

    ~User() {
        // Clear();
        cout << "User Destructor\n";
    }

    void Clear() {
        for (Card* c : cards) {
            delete c;
        }
        cards.clear();
    }

    // Setters & Getters
    const string& GetEmail() const {
		return email;
	}

	void SetEmail(const string& email) {
		this->email = email;
	}

	const string& GetName() const {
		return name;
	}

	void SetName(const string& name) {
		this->name = name;
	}

	const string& GetPassword() const {
		return password;
	}

	void SetPassword(const string& password) {
		this->password = password;
	}

	const string& GetUserName() const {
		return user_name;
	}

	void SetUserName(const string& userName) {
		user_name = userName;
	}

    int GetItinerariesCount() {
        return itineraries.size();
    }

    vector<Itinerary>& GetItineraries() {
        return itineraries;
    }

    const vector<Card*>& GetCards() const {
        return cards;
    }
    // Setters & Getters End

    string ToString() const {
		ostringstream oss;
		oss << "Name: " << user_name;
		oss << "\n";
		oss << "Email: " << email << "\n";
		oss << "User name: " << user_name << "\n";
		return oss.str();
	}

	void Read(const string &user_name) {
		SetUserName(user_name);

		string str;

		cout << "Enter password (no spaces): ";
		cin >> str;
		SetPassword(str);

		cout << "Enter name (no spaces): ";
		cin >> str;
		SetName(str);

		cout << "Enter email (no spaces): ";
		cin >> str;
		SetEmail(str);
	}

    bool MakeItinerary() {
        Itinerary it;

        if (it.MakeItineraryReservations(it)) {
            itineraries.push_back(it);
            cout << "\nItinerary reserved\n";
            return true;
        }
        cout << "\nItinerary is Canceled (NULL)\n";
        return false;
    }

    void LoadCardData() {
        Card* c1 = new CreditCard();
        c1->SetName(GetName());
        c1->SetAddress("Egypt-Elbehira-Elshennay");
        c1->SetCCV(121880001);
        c1->SetExpiryDate("12-2-2027");
        c1->SetId("23-454-001-12");
        Card* c2 = new DebitCard();
        c2->SetName(GetName());
        c2->SetAddress("Egypt-Cairo-Abbasya");
        c2->SetCCV(23029236);
        c2->SetExpiryDate("22-6-2030");
        c2->SetId("98-343-005-12");
        cards.push_back(c1);
        cards.push_back(c2);
    }

    vector<string> GetCardsInfo() {
        vector<string> cards_info;
        for (int i = 0; i < (int) cards.size(); ++i) {
            cards_info.push_back(cards[i]->ToString());
        }
        return cards_info;
    }
};

class UsersManager {
private:
    User* current_user {nullptr};
    map<string, User*> username_to_user_map;

public:
    UsersManager() {
        cout << "UsersManager Constructor\n";
    }

    ~UsersManager() {
        Clear();
        cout << "UsersManager Destructor\n";
    }

    UsersManager(const UsersManager&) = delete;
    void operator=(const UsersManager&) = delete;

    void Clear() {
        for (auto pair_ : username_to_user_map) {
            delete pair_.second;
            pair_.second = nullptr;
        }
        current_user = nullptr;
    }

    void LoadDatabase() {
		if (username_to_user_map.size() > 0)
			return;		// let's assume 1 run for this system only

		cout << "UsersManager: LoadDatabase\n";

		Clear();
		// Some "Dummy Data" for simplicity
		User* user1 = new User();
		user1->SetUserName("mohammad");
		user1->SetPassword("111");
		user1->SetEmail("mohammad@gmail.com");
		user1->SetName("Mohammad Mahmoud Ismail");
        user1->LoadCardData();
		username_to_user_map[user1->GetUserName()] = user1;

		User* user2 = new User();
		user2->SetUserName("hamza");
		user2->SetPassword("222");
		user2->SetEmail("hamza@gmail.com");
		user2->SetName("Hamaza Mahmoud Ismail");
        user2->LoadCardData();
		username_to_user_map[user2->GetUserName()] = user2;
	}

    void AccessSystem() {
        int choice = ShowMenu({"Login", "Sign Up"});
        if (choice == 1)
            DoLogin();
        else
            DoSignUp();
    }

    void DoLogin() {
        LoadDatabase();

        while (true) {
			string user_name, pass;
			cout << "Enter user name (no spaces): ";
			cin >> user_name;
			cout << "Enter password (no spaces): ";
			cin >> pass;

            if (!username_to_user_map.count(user_name)) {
                cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
            }
            User* user_exist = username_to_user_map.find(user_name)->second;

            if (pass != user_exist->GetPassword()) {
                cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
            }

            current_user = user_exist;
            break;
        }
    }

    void DoSignUp() {
        string user_name;
		while (true) {
			cout << "Enter user name (No spaces): ";
			cin >> user_name;

			if (username_to_user_map.count(user_name))
				cout << "Already used. Try again\n";
			else
				break;
		}
        current_user = new User();
		current_user->Read(user_name);
		string t = current_user->GetUserName();
		username_to_user_map[t] = current_user;
    }

    User* GetCurrentUser() {
        return current_user;
    }
};

class UserView {
private:
    UsersManager &users_manager;

public:
    UserView(UsersManager& users_manager) :
                    users_manager(users_manager){
    }

    void Display() {
		const User* user = users_manager.GetCurrentUser();

        while (true) {
            cout << "\n\nHello " << user->GetName() << " | User View\n";

            vector<string> menu = {"View Profile", "Make Itinerary", "List My Itineraries", "Logout"};
            int choice = ShowMenu(menu);

            if (choice == 1) {
                ViewProfile();
            } else if (choice == 2) {
                MakeItinerary();
            } else if (choice == 3) {
                ListMyItineraries();
            } else {
                break;
            }
        }
	}

	void ViewProfile() {
		const User* user = users_manager.GetCurrentUser();

		cout << "\n" << user->ToString() << "\n";
	}

    void MakePayment() {
        cout << "\nSelect a payment choice:\n";
        ShowMenu(users_manager.GetCurrentUser()->GetCardsInfo()); // We can take a choice to determine the card we pay from then compelete our process, if we want
        cout << "\nMoney Withdraw Successfully\n";
        cout << "Itinerary Reserved Susseccfully\n";
    }

    bool MakeItinerary() {
        if (!users_manager.GetCurrentUser()->MakeItinerary())
            return false;
        MakePayment();
        return true;
    }

    void ListMyItineraries() {
        users_manager.GetCurrentUser()->GetItineraries();
    
        if (!(users_manager.GetCurrentUser()->GetItinerariesCount() > 0)) {
            cout << "\nYou have made no itineraries for now\n";
            return;
        }
        cout << "********************* " << users_manager.GetCurrentUser()->GetUserName() << ":  T O T A L   I T I N E R A R I E S *********************\n\n";

        for (int i = 0; i < users_manager.GetCurrentUser()->GetItinerariesCount(); ++i) {
            cout << "Itinerary # " << i + 1 << ":\n";
            users_manager.GetCurrentUser()->GetItineraries()[i].print();
            cout << "\n";
        }

        cout << "\n***************************************************************************************\n";
    }

};

class ExpideaApp {
private:
    UsersManager* users_manager;
public:

    ExpideaApp() : users_manager(new UsersManager()) {
        cout << "\nExpidea Constructor\n";
    }

    ~ExpideaApp() {
        if (users_manager != nullptr) {
            delete users_manager;
            users_manager = nullptr;
        }
        cout << "\nExpidea Destructor\n";
    }

    void Run() {
        while (true) {
            users_manager->AccessSystem();

            UserView view(*users_manager);
            view.Display();
        }
    }
};


int main()
{
    ExpideaApp myapp;
    myapp.Run();
    return 0;
}
