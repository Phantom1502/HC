#pragma once

#include "libPlatform.h"
#define AppId @"858"
#define AppKey @"kSsOaxrM"
#define MerchantId @"323"
class libDownJoy: public libPlatform
{
private:
    bool mEnableLogin;
    BUYINFO mBuyInfo;
    std::string mNickName;
    std::string mUin;
public:
    void _enableLogin(){mEnableLogin = true;}
    void _disableLogin(){mEnableLogin = false;}
	BUYINFO getBuyInfo(){return mBuyInfo;}
	/**
	call this function first of all.
	NOTICE: Platform should call _boardcastInitDone to notify client logic WHEN initialization is done.
	*/
	virtual void init(bool privateLogin = false);

	/**
	MUST call this function AFTER initialization is done(after call back function).
	NOTICE: Platform should call _boardcastUpdateCheckDone to notify client logic WHEN update checking is done.
	*/
    virtual void updateApp();

	/**
	MUST call this function AFTER updating is done(after call back function).
	NOTICE: Platform should call _boardcastLoginResult to notify client logic WHEN login is done.
	*/
	virtual void login();

	/** logout platform*/
	virtual void logout();

	/** optional: finalize the platform*/
	virtual void final();

	/** show the platform window to switch users */
	virtual void switchUsers();

	/** buy platform RMB*/
	virtual void buyGoods(BUYINFO&);
	
	/** call platform open bbs function. if the platform doesn't have this usage, just open an url! */
	virtual void openBBS();
	/** call platform open feedback function. if the platform doesn't have this usage, just open an email link! */
	virtual void userFeedBack();
	/** optional: call platform open game pause function.*/
	virtual void gamePause();

	/** check whether is logined */
	virtual bool getLogined();

	/** IMPORTANT: get the only ID for game. MUST be unique! */
	virtual const std::string& loginUin();
	/** optional: get the session ID.*/
	virtual const std::string& sessionID();
	/** optional: get the nick name. which is shown on the loading scene */
	virtual const std::string& nickName();
    virtual void notifyEnterGame(){};
	virtual const float getPlatformChangeRate(){return 1.0f;}
	const std::string getClientChannel();
    std::string getPlatformMoneyName();
	virtual const unsigned int getPlatformId();
    virtual void setNickName(const std::string nickName) { mNickName=nickName;};
    virtual void setLoginUin(const std::string loginuin) { mUin=loginuin;};
};


