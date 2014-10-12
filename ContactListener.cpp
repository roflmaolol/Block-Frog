#include "ContactListener.h"

ContactListener::ContactListener() {
	for(int i = 0; i < 10; i++) {
        numFootContacts[i] = 0;
        recentHookContacts[i] = NULL;
    }
}

int ContactListener::getNumFootContacts(int birthNumber) {
    return numFootContacts[birthNumber-1];
}

b2Body* ContactListener::getRecentHookContact(int birthNumber) {
    return recentHookContacts[birthNumber-1];
}

void ContactListener::setHookActive(bool active) {
	hookIsActive = active;
}

void ContactListener::removeRecentHookContact(int birthNumber) {
    recentHookContacts[birthNumber-1] = NULL;
}

// DESCRIPTION:
// Fixtures can be registered with a user data of a certain size.
// EXAMPLE: footSensorFixture->SetUserData( (void*)3 );
// REGISTERED FIXTURES:
// 3: Foot sensor
// 4: The tip of the hook
// 5: Dynamic box in world

// Checking if contact between bodies has started
void ContactListener::BeginContact(b2Contact* contact) {
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    
//    cout << "Foot contacts: " << numFootContacts << endl;
	switch((uintptr_t)fixtureAUserData) {
        case 1:
//            cout << "foot contact " << 1 << endl;
            numFootContacts[1-1]++;
            break;
        case 2:
//            cout << "foot contact " << 2 << endl;
            numFootContacts[2-1]++;
            break;
        case 3:
//            cout << "foot contact " << 3 << endl;
            numFootContacts[3-1]++;
            break;
        case 4:
//            cout << "foot contact " << 4 << endl;
            numFootContacts[4-1]++;
            break;
        case 11:
//            cout << "hook contact " << 11 << endl;
            if((uintptr_t)fixtureBUserData == 99) {
                recentHookContacts[11-11] = contact->GetFixtureB()->GetBody();
            }
            break;
        case 12:
//            cout << "hook contact " << 12 << endl;
            if((uintptr_t)fixtureBUserData == 99) {
                recentHookContacts[12-11] = contact->GetFixtureB()->GetBody();
            }
            break;
        case 13:
            if((uintptr_t)fixtureBUserData == 99) {
                recentHookContacts[13-11] = contact->GetFixtureB()->GetBody();
            }
            break;
        case 14:
            if((uintptr_t)fixtureBUserData == 99) {
                recentHookContacts[14-11] = contact->GetFixtureB()->GetBody();
            }
            break;
            
        default: ;
    }
    
    switch((uintptr_t)fixtureBUserData) {
        case 1:
//            cout << "foot contact " << 1 << endl;
            numFootContacts[1-1]++;
            break;
        case 2:
//            cout << "foot contact " << 2 << endl;
            numFootContacts[2-1]++;
            break;
        case 3:
//            cout << "foot contact " << 3 << endl;
            numFootContacts[3-1]++;
            break;
        case 4:
//            cout << "foot contact " << 4 << endl;
            numFootContacts[4-1]++;
            break;
        case 11:
//            cout << "hook contact " << 11 << endl;
            if((uintptr_t)fixtureAUserData == 99) {
                recentHookContacts[11-11] = contact->GetFixtureA()->GetBody();
            }
            break;
        case 12:
            if((uintptr_t)fixtureAUserData == 99) {
                recentHookContacts[12-11] = contact->GetFixtureA()->GetBody();
            }
            break;
        case 13:
            if((uintptr_t)fixtureAUserData == 99) {
                recentHookContacts[13-11] = contact->GetFixtureA()->GetBody();
            }
            break;
        case 14:
            if((uintptr_t)fixtureAUserData == 99) {
                recentHookContacts[14-11] = contact->GetFixtureA()->GetBody();
            }
            break;
            
        default: ;
    }
    
    
//    if((uintptr_t)fixtureAUserData == 3) {
//		
//    }
//    else if((uintptr_t)fixtureAUserData == 4 && hookIsActive) {
//        if((uintptr_t)fixtureBUserData == 5) {
//        	recentHookContact = contact->GetFixtureB()->GetBody();
//        }
//    }
//    
//    if ((uintptr_t)fixtureBUserData == 3) {
//        numFootContacts++;
//    }
//    else if ((uintptr_t)fixtureBUserData == 4 && hookIsActive) {
//        if((uintptr_t)fixtureAUserData == 5) {
//	        recentHookContact = contact->GetFixtureA()->GetBody();
//        }
//    }
}

// Checking if contact between bodies has ended
void ContactListener::EndContact(b2Contact* contact) {
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    
   	switch((uintptr_t)fixtureAUserData) {
        case 1:
//            cout << "foot lost contact " << 1 << endl;
            numFootContacts[1-1]--;
            break;
        case 2:
//            cout << "foot lost contact " << 2 << endl;
            numFootContacts[2-1]--;
            break;
        case 3:
//            cout << "foot lost contact " << 3 << endl;
            numFootContacts[3-1]--;
            break;
        case 4:
//            cout << "foot lost contact " << 4 << endl;
            numFootContacts[4-1]--;
            break;
        case 11:
//            cout << "hook lost contact " << 11 << endl;
            break;
        case 12:
//            cout << "hook lost contact " << 12 << endl;
            break;
            
        default: ;
    }
    
    switch((uintptr_t)fixtureBUserData) {
        case 1:
//            cout << "foot lost contact " << 1 << endl;
            numFootContacts[1-1]--;
            break;
        case 2:
//            cout << "foot lost contact " << 2 << endl;
            numFootContacts[2-1]--;
            break;
        case 3:
//            cout << "foot lost contact " << 3 << endl;
            numFootContacts[3-1]--;
            break;
        case 4:
//            cout << "foot lost contact " << 4 << endl;
            numFootContacts[4-1]--;
            break;
        case 11:
//            cout << "hook lost contact " << 11 << endl;
            break;
        case 12:
//            cout << "hook lost contact " << 12 << endl;
            break;
            
        default: ;
    }
}