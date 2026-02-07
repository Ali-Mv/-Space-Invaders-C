#pragma warning(disable:4996)
#include "defines.h"

int main() {
	WelcomeUser();
	while (1) {
		
		int login_status = AskPlayerLogin();

		if (login_status == want_exit)
			break;
		switch (login_status) {

			case user_exists_not :
				SignUp();
				break;
			case user_exists :
				Login();
				break;
		}

		while (1) {
			int choice = ShowMenu();
			if (choice == logout)
				break;
			switch (choice) {

			case start_game:
				GoGameLoop();
				break;
			case show_leaderbord:
				ShowLeaderBord();
				break;
			case shop:
				GoShop();
				break;
			case edit_user_info:
				EditInfo();
				break;
			}

		}



		
	}
}
