#include <iostream>
#include <memory>
#include <vector>

using namespace std;

////// 1️⃣ Singleton - Video Streaming Service //////
class VideoStreamingService {
private:
    static VideoStreamingService* instance;
    VideoStreamingService() {
        cout << "Initializing Video Streaming Service...\n";
    }

public:
    static VideoStreamingService* getInstance() {
        if (instance == nullptr) {
            instance = new VideoStreamingService();
        }
        return instance;
    }

    void streamVideo(const string& title) {
        cout << "Streaming: " << title << endl;
    }
};

// Initialize static instance
VideoStreamingService* VideoStreamingService::instance = nullptr;

////// 2️⃣ Factory - Video Content Factory //////
class VideoContent {
public:
    virtual string getTitle() = 0;
    virtual ~VideoContent() = default;
};

class Movie : public VideoContent {
private:
    string title;
public:
    Movie(const string& t) : title(t) {}
    string getTitle() override {
        return "Movie: " + title;
    }
};

class TVShow : public VideoContent {
private:
    string title;
public:
    TVShow(const string& t) : title(t) {}
    string getTitle() override {
        return "TV Show: " + title;
    }
};

class Documentary : public VideoContent {
private:
    string title;
public:
    Documentary(const string& t) : title(t) {}
    string getTitle() override {
        return "Documentary: " + title;
    }
};

class VideoFactory {
public:
    static shared_ptr<VideoContent> createVideo(const string& type, const string& title) {
        if (type == "Movie") return make_shared<Movie>(title);
        if (type == "TVShow") return make_shared<TVShow>(title);
        if (type == "Documentary") return make_shared<Documentary>(title);
        throw invalid_argument("Invalid video content type");
    }
};

////// 3️⃣ Facade - Streaming Facade //////
class StreamingFacade {
private:
    VideoStreamingService* service;
public:
    StreamingFacade() {
        service = VideoStreamingService::getInstance();
    }

    void playVideo(shared_ptr<VideoContent> video) {
        cout << "Authenticating user...\n";
        cout << "Buffering video...\n";
        cout << "Applying DRM protection...\n";
        service->streamVideo(video->getTitle());
    }

    void stopVideo() {
        cout << "Stopping video playback...\n";
    }
};

////// 4️⃣ Proxy - Subscription Proxy //////
class SubscriptionProxy {
private:
    bool hasSubscription;
public:
    SubscriptionProxy(bool active) : hasSubscription(active) {}

    bool checkAccess() {
        if (!hasSubscription) {
            cout << "Access Denied: Subscription required!\n";
            return false;
        }
        return true;
    }
};

////// 5️⃣ Decorator - Video Features //////
class VideoDecorator : public VideoContent {
protected:
    shared_ptr<VideoContent> baseVideo;
public:
    VideoDecorator(shared_ptr<VideoContent> video) : baseVideo(video) {}
    virtual string getTitle() = 0;
};

class Subtitles : public VideoDecorator {
public:
    Subtitles(shared_ptr<VideoContent> video) : VideoDecorator(video) {}
    string getTitle() override {
        return baseVideo->getTitle() + " + Subtitles";
    }
};

class FourK : public VideoDecorator {
public:
    FourK(shared_ptr<VideoContent> video) : VideoDecorator(video) {}
    string getTitle() override {
        return baseVideo->getTitle() + " + 4K Quality";
    }
};

class DolbyAudio : public VideoDecorator {
public:
    DolbyAudio(shared_ptr<VideoContent> video) : VideoDecorator(video) {}
    string getTitle() override {
        return baseVideo->getTitle() + " + Dolby Audio";
    }
};

////// Main Execution //////
int main() {
    // User Subscription Check
    SubscriptionProxy userProxy(false); // Set to true to allow access

    if (!userProxy.checkAccess()) {
        return 0; // Block access if no subscription
    }

    // Create Video using Factory
    shared_ptr<VideoContent> video = VideoFactory::createVideo("Movie", "Inception");

    // Add Features using Decorator
    video = make_shared<Subtitles>(video);
    video = make_shared<FourK>(video);

    // Streaming Facade to Handle Video Playback
    StreamingFacade facade;
    facade.playVideo(video);
    facade.stopVideo();

    return 0;
}
