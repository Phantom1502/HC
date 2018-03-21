/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>
#include <curl/curl.h>

#include "cocos2d.h"
#include "../ExtensionMacros.h"

NS_CC_EXT_BEGIN




#define     AMG_STATUS_NONE                     0
#define     AMG_STATUS_CHECKING_VERSION         1
#define     AMG_STATUS_VERSION_CHECKED          2
#define     AMG_STATUS_DOWNLOADING              3
#define     AMG_STATUS_DOWNLOAD_FINISHED        4
#define     AMG_STATUS_DOWNLOADED_FAILED        5
//#define     AMG_STATUS_BINARY_UPDATED           6


class AssetsFileInfo
{
public:
    long size;
    std::string file;
    std::string hash;
};


/*
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And there should be a file named
 *  version in the server, which contains version code.
 */
class AssetsManager
{
public:

    

    AssetsManager(std::string& storagePatch, std::vector<std::string > & versionServerDirs, const char* versionFileUrl);
    ~AssetsManager();
  
    /* @brief Creates a AssetsManager with new package url and version code url.
     *        AssetsManager will use the value returned by CCFileUtils::getWritablePath() as storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     */
  //  AssetsManager(const char* packageUrl, const char* versionFileUrl);
    
    /* @brief Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     * @param storagePath The path to store downloaded resources.
     */
  //  AssetsManager(const char* packageUrl, const char* versionFileUrl, const char* storagePath);
    
    
    virtual float getProgress();
    virtual int   getStatusCode();
   
//    getProgress()
//    checkStoragePath()
//    std::string *getProgressDesc()
//    checkUpdate()
//    getVersionServer()
//    createDirectory(char const*)
//    setProgress(int, long long, long long)
//    getAUCode()
//    setSearchPath()
//    getAUStep()
//    sharedManager()
//    getCurrentVersion()
//    uncompress(char const*)
//    getDownloadedVersion()
//    update()
//    getFileFromVersionServer(char const*)
    
    std::string& getVersionServer();
    unsigned char* getFileFromVersionServer(const char* file, size_t *pSize);
    
    
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual void checkUpdate();
    
    virtual bool  isNeedUpdate();

    
    /* @brief Download new package if there is a new version, and uncompress downloaded zip file.
     *        Ofcourse it will set search path that stores downloaded files.
     */
    virtual void update();
    
    /* @brief Gets url of package.
     */
  //  const char* getPackageUrl() const;
    
    /* @brief Sets package url.
     */
    //void setPackageUrl(const char* packageUrl);
    
    /* @brief Gets version file url.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief Gets version file url.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets current version code.
     */
    std::string getVersion();
    
    /* @brief Deletes recorded version code.
     */
    void deleteVersion();
    
    /* @brief Gets storage path.
     */
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const char* storagePath);
    
    //static void setSearchPath();
    void setSearchPath();
    static AssetsManager * sharedManager();
    bool isPatchDataExist();
    int removePatchesData();
    bool isBinaryUpdated();
    
    void reset();
    
    void addBytesLoade(size_t n);
    
    void onDownloadComplete();
    
    std::string & getProgressDesc();
    
    bool isOnCompleteCalled();
    
    void onVersionCheckComplete();
    
    int isCheckingVersionRunning();
    
    bool isPendingUpdateCall();
    int isDownloading();
    bool isScriptChanged();
    
    size_t getScripteFileListSize();
protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    bool applyPatchFiles();
    bool createPatchesSubDirs(const char *rootPath);
    static AssetsManager *m_instance;
    
    static void* networkDownloadThread(void *data);
    static void* networkCheckVersionThread(void *data);
    static void* downloadWorker(void *data);
    
    bool requestLatestVersion();
    static void setCheckVersionRunning(int val);
    
private:
    //! The path to store downloaded resources.
    std::string _storagePath;
    std::vector<std::string> _serverDirs;
   
    //! The version of downloaded resources.
    std::string _versionResponse;
    
  //  std::string _packageUrl;
    std::string _versionFileUrl;
    bool _binaryUpdated;
    std::vector<AssetsFileInfo> _fileList;
    
   
    
    size_t _bytesTotoal;
    size_t _bytesLoaded;
    
    int _numFilesApplies;
    int _totalFiles;
    int    _isApplyDownloadFiles;
    
    int _currentStatusCode;
    
    bool _onCompleteCalled;
    
    std::string _downloadDesc;
    
    std::string _recordedVersion;
    
    std::string _latestVersion;
    
    static int _checkingThreadRunning;
    
    bool _pendingUpdateCall;
    
    int _isDownloading;
    
    static bool curl_global_inited;
};

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
