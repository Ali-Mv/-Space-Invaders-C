#include "defines.h"

User currentUser;

int main() {

	WelcomeUser();


	while (1) {
		
		int login_status = AskPlayerLogin();

		if (login_status == want_exit) 
			break;
		else if (login_status == Forgot_Password) {
			ForgotPassword();
			continue; 
		}
		else if (login_status == user_exists_not) {
			SignUp();
		}
		else if (login_status == user_exists) {
			Login();
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
