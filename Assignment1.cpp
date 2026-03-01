#include <iostream>
#include <string>
using namespace std;

// -------------------- Car Class --------------------

class Car {

private:
    string brand, model;
    int year;
    float mileage;
    double price;
    bool status; // available/sold

public:
    Car() : brand("Unknown"), model("Unknown"), year(0), mileage(0.0), price(0.0), status(true) {}

    Car(string b, string m, int y, double p, float mil) : brand(b), model(m), year(y), mileage(mil), price(p), status(true) {}

    Car(const Car &c) { 
        brand = c.brand; 
        model = c.model; 
        year = c.year; 
        mileage = c.mileage;
        price = c.price; 
        status = c.status; 
    }

    void displayInfo() const {
        cout << brand << " | " << model << " | (" << year << ") | Rs." << price << " | Mileage: " << mileage << endl;
    }

    void updateDetails(string b, string m, int y, double p, float mil) {
        brand = b; 
        model = m; 
        year = y; 
        price = p; 
        mileage = mil;
    }

    double calculateDepreciation() const { 
        return price * 0.85; 
    }

    void markAsSold() { 
        status = false; 
    }

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    float getMileage() const { return mileage; }
    double getPrice() const { return price; }
    int getYear() const { return year; }
};

// -------------------- Review Class --------------------

class Review {

private:
    const int reviewID;
    const int reviewerID, sellerID;
    int rating;
    string comment, date;

public:
    Review(int id=0, int r=0, int s=0, int rate=0, string c="NA", string d="NA")
        : reviewID(id), reviewerID(r), sellerID(s), rating(rate), comment(c), date(d) {}

    void addReview() { 
        cout << "Review added: " << rating << "/5 - " << comment << endl; 
    }

    void editReview(string newComment, int newRating) { 
        comment=newComment; 
        rating=newRating; 
    }

    void deleteReview() { 
        cout << "Review deleted.\n"; 
    }

    void displayReview() { 
        cout << "Review: " << rating << "/5 - " << comment << " (" << date << ")" << endl; 
    }

};

// -------------------- Seller Class(composition) --------------------

class Seller {

private:
    int sellerID;
    string name, contact;
    double rating;
    Car cars[10];
    int carCount;
    Review sellerReview; //composition

public:
    Seller(int id=0, string n="NA", string c="NA", double r=0.0, Review rev = Review()) : sellerID(id), name(n), contact(c), carCount(0), rating(r), sellerReview(rev){}

    void addCar(Car c) { 
        if(carCount < 10) 
        cars[carCount++] = c; 
    }

    void removeCar(int index) {
        if(index >= 0 && index < carCount) {
            for(int i=index; i<carCount-1; i++) cars[i] = cars[i+1];
            carCount--;
        }
    }

    void updateCarListing(int index, Car c) { 
        if(index >= 0 && index < carCount) cars[index] = c; 
    }

    void showCars() { 
        for(int i=0; i<carCount; i++) cars[i].displayInfo(); 
    }

    void displayInfo() const {
        cout << "Seller Information:\n";
        cout << "ID: " << sellerID << " | Name: " << name << " | Contact: " << contact << " | Rating: " << rating << "\n";
    }

    void showReview() {
        sellerReview.displayReview();
    }
};

// -------------------- Marketplace Class --------------------

class Marketplace {

private:
    string systemName;
    Car allListings[50];
    int listingCount;
    Seller* sellers[20];
    int sellerCount;
    static int totalListings;
    static int totalUsers;

public:
    Marketplace(string name="Car Marketplace") : systemName(name), listingCount(0), sellerCount(0) {}

    void addListing(Car c) { 
        if(listingCount < 50) { 
            allListings[listingCount++] = c; 
            totalListings++; 
        } 
    }

    void deleteListing(int index) {
        if(index >= 0 && index < listingCount) {
            for(int i=index; i<listingCount-1; i++) allListings[i] = allListings[i+1];
            listingCount--; totalListings--;
        }
    }

    void searchListings() {
        int response;
        cout << "To search by brand enter 1.\nTo search by model enter 2.\nTo search by price enter 3.\nTo search by year enter 4.\nTo search by mileage enter 5.\n";
        cin >> response;
        switch (response) {
            case 1: {
                string brand;
                cout << "Enter brand name: ";
                cin >> brand;
                for(int i=0; i<listingCount; i++) {
                    if(allListings[i].getBrand() == brand) allListings[i].displayInfo();
                }
                break;
            }
            case 2: {
                string model;
                cout << "Enter model: ";
                cin >> model;
                for(int i=0; i<listingCount; i++) {
                    if(allListings[i].getModel() == model) allListings[i].displayInfo();
                }
                break;
            }
            case 3: {
                double price;
                cout << "Enter price: ";
                cin >> price;
                for(int i=0; i<listingCount; i++) {
                    if(allListings[i].getPrice() == price) allListings[i].displayInfo();
                }
                break;
            }
            case 4: {
                int year;
                cout << "Enter year: ";
                cin >> year;
                for(int i=0; i<listingCount; i++) {
                    if(allListings[i].getYear() == year) allListings[i].displayInfo();
                }
                break;
            }
            case 5: {
                float mileage;
                cout << "Enter mileage: ";
                cin >> mileage;
                for(int i=0; i<listingCount; i++) {
                    if(allListings[i].getMileage() == mileage) allListings[i].displayInfo();
                }
                break;
            }
            default: 
                cout << "Invalid Input\n";
        }    
    }

    void showAllListings() { 
        for(int i=0; i<listingCount; i++) allListings[i].displayInfo(); 
    }


    static int getTotalListings() { 
        return totalListings; 
    }

    Car* getListings() { 
        return allListings; 
    }

    int getListingCount() const { 
        return listingCount; 
    }

    void registerSeller(Seller* s) {
        if(sellerCount < 20) {
            sellers[sellerCount++] = s;
        }
    }
};

int Marketplace::totalListings = 0;
int Marketplace::totalUsers = 0;

// -------------------- Buyer Class (aggregation)--------------------

class Buyer {

private:
    int buyerID;
    string name, contact, email;
    Car favorites[10];
    int favCount;
    Marketplace* market; //aggregation

public:
    Buyer(int id=0, string n="NA", string c="NA", string e="NA", Marketplace* m=nullptr) : buyerID(id), name(n), contact(c), email(e), favCount(0), market(m) {}

    void addFavorite(Car c) { 
        if(favCount < 10) favorites[favCount++] = c; 
    }

    void removeFavorite(int index) {
        if(index >= 0 && index < favCount) {
            for(int i=index; i<favCount-1; i++) favorites[i] = favorites[i+1];
            favCount--;
        }
    }

    void sendMessage(string msg) { 
        cout << "Buyer sent message: " << msg << endl; 
    }

    void searchCars(string brand) {
        if(market == nullptr) return;
        Car* cars = market->getListings();
        int size = market->getListingCount();

        for(int i=0; i<size; i++) {
            if(cars[i].getBrand() == brand)
                cars[i].displayInfo();
        }
    }
};

// -------------------- Admin Class(aggregation) --------------------

class Admin {

private:
    const int adminID;
    string name, email, role;
    int approvedListings[20];
    int removedListings[20];
    int approvedCount, removedCount;
    static int totalAdmins;

public:
    Admin(int id=0, string n="NA", string e="NA", string r="Moderator") : adminID(id), name(n), email(e), role(r), approvedCount(0), removedCount(0) {
        totalAdmins++;
    }
    // aggregation
    void approveListing(Car &c) { 
        cout << "Listing approved for: "; 
        c.displayInfo();
        approvedListings[approvedCount++] = adminID; 
    }

    void removeListing(Car cars[], int &size, int index) {
        if(index >= 0 && index < size) {
            for(int i=index; i<size-1; i++) cars[i] = cars[i+1];
            size--;
            removedListings[removedCount++]=adminID;
        }
    }

    static void displayTotalAdmins() {
        cout << "Total Admins: " << totalAdmins << endl;
    }

    void banSeller(Seller &s) {
        s.displayInfo();
        cout << "Seller banned\n";
    }
};

int Admin::totalAdmins=0;



// -------------------- Listing Class (Composition) --------------------

class Listing {

private:
    int listingID;
    Car car; // composition
    string datePosted;
    bool status;
    int views;

public:
    Listing(int id, Car c, string d) : listingID(id), car(c), datePosted(d), status(true), views(0) {}

    void activateListing() { 
        status = true; 
    }

    void deactivateListing() { 
        status = false; 
    }

    void updateListing(Car c) { 
        car=c; 
    }

    void showListing() { 
        car.displayInfo(); 
        cout << "Views: " << views << endl;
    }
};

// -------------------- Message Class --------------------

class Message {

private:
    const int messageID;
    const int senderID, receiverID;
    string content, timestamp;
    bool status;

public:
    Message(int id=0, int s=0, int r=0, string c="NA", string t="NA") : messageID(id), senderID(s), receiverID(r), content(c), timestamp(t), status(false) {}

    void sendMessage() { 
        cout << "Message sent: " << content << endl;
        status=true; 
    }
    void markAsRead() { 
        cout << "Message marked as read.\n"; 
    }
    void deleteMessage() {
        cout << "Message deleted.\n";
        status = false;
    }
    void replyMessage(string reply) {
        cout << "Reply: " << reply << endl;
    }

};

// -------------------- SearchFilter Class --------------------

class SearchFilter {

private:
    string brand, model;
    double minPrice, maxPrice;
    int minYear, maxMileage;

public:
    SearchFilter(string b="Any", string m="Any", double minP=0, double maxP=999999, int y=0, int mil=999999)
        : brand(b), model(m), minPrice(minP), maxPrice(maxP), minYear(y), maxMileage(mil) {}

    bool matchCar(const Car &c) const { 
        return (c.getBrand()==brand || brand=="Any"); 
    }

    void applyFilter(Car cars[], int size) { 
        for(int i=0; i<size; i++) {
            if(matchCar(cars[i])) cars[i].displayInfo();
        }
    }

    void resetFilter() { 
        brand="Any"; 
        model="Any"; 
        minPrice=0; 
        maxPrice=999999; 
        minYear=0; 
        maxMileage=999999; 
    }

    void showResults(Car cars[], int size) { 
        applyFilter(cars,size); 
    }
};

// -------------------- Payment Class --------------------

class Payment {

private:
    int paymentID;
    double amount;
    int buyerID, sellerID;
    string method;
    bool status;
    const double TAX_RATE = 0.15; // constant

public:
    Payment(int id=0, double a=0, int b=0, int s=0, string m="Cash")
        : paymentID(id), amount(a), buyerID(b), sellerID(s), method(m), status(false) {}

    void processPayment() { 
        status=true; 
        cout << "Payment processed: $" << amount*(1+TAX_RATE) << endl; 
    }

    void refundPayment() { 
        status=false; 
        cout << "Payment refunded.\n"; 
    }

    void generateInvoice() { 
        cout << "Invoice generated for $" << amount << endl; 
    }

    void verifyPayment() { 
        cout << "Payment verified.\n"; 
    }

};

// -------------------- Main Function --------------------

int main() {
    Marketplace market;
    Seller s1(1, "Ali", "0300-1234567");
    market.registerSeller(&s1);
    Buyer b1(101, "Rabisa", "0333-9876543", "NA", &market);
    Admin a1(999, "Admin", "admin@market.com");

    
    Car c1("Toyota", "Corolla", 2020, 25000, 30000);
    Car c2("Honda", "Civic", 2019, 22000, 40000);

    Car* const ptr1 = &c1;        
    Car* const ptr2 = &c2;

    Car* const ptr3 = market.getListings(); 

    Seller* const ptr4 = &s1;
    Buyer* const ptr5 = &b1;

    // Seller adds cars
    s1.addCar(c1);
    s1.addCar(c2);

    // Marketplace adds listings
    market.addListing(c1);
    market.addListing(c2);

    // Buyer searches
    cout << "\nBuyer searching for Toyota cars:\n";
    b1.searchCars("Toyota");

    // Admin approves
    a1.approveListing(c1);

    // Show all listings
    cout << "\nAll Listings:\n";
    market.showAllListings();

    // Payment
    Payment p1(1, 25000, 101, 1, "Credit Card");
    p1.processPayment();

    // Review
    Review r1(1, 101, 1, 5, "Excellent seller!");
    r1.displayReview();

    cout << "\nTotal Listings: " << Marketplace::getTotalListings() << endl;
}