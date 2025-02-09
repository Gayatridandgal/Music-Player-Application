/*You are developing a music player application in C++ that allows users to create playlists, play songs,
 and manage their music library. How would you design classes to represent music files, playlists,
  audio playback functionality, and user preferences for the music player*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MusicFile {
private:
    string title;
    string artist;
    int duration; // in seconds

public:
    // Constructor
    MusicFile(const string& title, const string& artist, int duration)
        : title(title), artist(artist), duration(duration) {}

    // Getters
    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    int getDuration() const { return duration; }
};

class Playlist {
private:
    string name;
    vector<MusicFile> songs;

public:
    Playlist(const string& name) : name(name) {}

    // Add a song to the playlist
    void addSong(const MusicFile& song) {
        songs.push_back(song);
    }

    // Remove a song from the playlist by index
    void removeSong(size_t index) {
        if (index < songs.size()) {
            songs.erase(songs.begin() + index);
        }
    }

    // Get all songs
    vector<MusicFile> getSongs() const {
        return songs;
    }

    // Get playlist name
    string getName() const {
        return name;
    }

    // Display songs in the playlist
    void viewSongs() const {
        cout << "Songs in playlist " << name << ":" << endl;
        for (size_t i = 0; i < songs.size(); ++i) {
            cout << (i + 1) << ": " << songs[i].getTitle() << " by " << songs[i].getArtist() << " (" << songs[i].getDuration() << " seconds)" << endl;
        }
    }
};

class AudioPlayer {
private:
    MusicFile* currentSong;
    bool isPlaying;

public:
    AudioPlayer() : currentSong(nullptr), isPlaying(false) {}

    // Play a song
    void play(MusicFile* song) {
        currentSong = song;
        isPlaying = true;
        cout << "Playing: " << song->getTitle() << " by " << song->getArtist() << endl;
        // Actual audio playback code goes here
    }

    // Pause the current song
    void pause() {
        if (isPlaying && currentSong != nullptr) {
            isPlaying = false;
            cout << "Paused: " << currentSong->getTitle() << endl;
            // Actual pause code goes here
        }
    }

    // Stop the current song
    void stop() {
        if (currentSong != nullptr) {
            isPlaying = false;
            cout << "Stopped: " << currentSong->getTitle() << endl;
            currentSong = nullptr;
            // Actual stop code goes here
        }
    }

    // Skip to the next song in a playlist
    void skipToNext(Playlist& playlist) {
        if (currentSong != nullptr) {
            auto songs = playlist.getSongs();
            for (size_t i = 0; i < songs.size(); ++i) {
                if (&songs[i] == currentSong && i + 1 < songs.size()) {
                    play(&songs[i + 1]);
                    return;
                }
            }
        }
    }
};

class UserPreferences {
private:
    int volume; // 0 to 100
    bool shuffle;
    string theme;

public:
    UserPreferences(int volume = 50, bool shuffle = false, const string& theme = "Light")
        : volume(volume), shuffle(shuffle), theme(theme) {}

    // Getters and setters
    int getVolume() const { return volume; }
    void setVolume(int volume) { this->volume = volume; }

    bool isShuffle() const { return shuffle; }
    void setShuffle(bool shuffle) { this->shuffle = shuffle; }

    string getTheme() const { return theme; }
    void setTheme(const string& theme) { this->theme = theme; }
};

void displayMenu() {
    cout << endl<<"+--------------------------+" << endl;
    cout << "|  MUSIC PLAYER MENU:      |" << endl;
    cout << "+--------------------------+" << endl<<endl;
    cout << "1. Create Playlist" << endl;
    cout << "2. Add Song to Playlist" << endl;
    cout << "3. View Songs in Playlist" << endl;
    cout << "4. View Playlists" << endl;
    cout << "5. Play Song" << endl;
    cout << "6. Pause Song" << endl;
    cout << "7. Stop Song" << endl;
    cout << "8. Skip to Next Song" << endl;
    cout << "9. Set User Preferences" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Playlist> playlists;
    AudioPlayer player;
    UserPreferences prefs;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter playlist name: ";
                string name;
                cin.ignore();
                getline(cin, name);
                playlists.emplace_back(name);
                cout << "Playlist " << name << " created." << endl;
                break;
            }
            case 2: {
                if (playlists.empty()) {
                    cout << "No playlists available. Create a playlist first." << endl;
                    break;
                }
                cout << "Enter playlist index: ";

              //  cin >> index;
                 int index;
              try{
                  cin >> index;
                  if(index!=int()){
                    throw runtime_error("failed");
                  }}
                  catch(runtime_error  &e){
                  cout<<"Enter number:}"<<endl;

              }
                if (index < 1 || index > playlists.size()) {
                    cout << "Invalid playlist index." << endl;
                    break;
                }
                cout << "Enter song details (title artist duration): ";
                string title, artist;
                int duration;
                cin.ignore();
                getline(cin, title);
                getline(cin, artist);
                cin >> duration;
                MusicFile song(title, artist, duration);
                playlists[index - 1].addSong(song);
                cout << "Song " << title << " added to playlist " << playlists[index - 1].getName() << "." << endl;
                break;
            }
            case 3: {
                if (playlists.empty()) {
                    cout << "No playlists available. Create a playlist first." << endl;
                    break;
                }
                cout << "Enter playlist index: ";
                int index;
                cin >> index;
                if (index < 1 || index > playlists.size()) {
                    cout << "Invalid playlist index." << endl;
                    break;
                }
                playlists[index - 1].viewSongs();
                break;
            }
            case 4: {
                if (playlists.empty()) {
                    cout << "No playlists available." << endl;
                    break;
                }
                cout << "Available playlists:" << endl;
                for (size_t i = 0; i < playlists.size(); ++i) {
                    cout << (i + 1) << ": " << playlists[i].getName() << endl;
                }
                break;
            }
            case 5: {
                if (playlists.empty()) {
                    cout << "No playlists available. Create a playlist first." << endl;
                    break;
                }
                cout << "Enter playlist index: ";
                int index;
                cin >> index;
                if (index < 1 || index > playlists.size()) {
                    cout << "Invalid playlist index." << endl;
                    break;
                }
                cout << "Enter song index: ";
                int songIndex;
                cin >> songIndex;
                auto songs = playlists[index - 1].getSongs();
                if (songIndex < 1 || songIndex > songs.size()) {
                    cout << "Invalid song index." << endl;
                    break;
                }
                player.play(&songs[songIndex - 1]);
                break;
            }
            case 6: {
                player.pause();
                break;
            }
            case 7: {
                player.stop();
                break;
            }
            case 8: {
                if (playlists.empty()) {
                    cout << "No playlists available. Create a playlist first." << endl;
                    break;
                }
                cout << "Enter playlist index: ";
                int index;
                cin >> index;
                if (index < 1 || index > playlists.size()) {
                    cout << "Invalid playlist index." << endl;
                    break;
                }
                player.skipToNext(playlists[index - 1]);
                break;
            }
            case 9: {
                cout << "Enter volume (0-100): ";
                int volume;
                cin >> volume;
                prefs.setVolume(volume);
                cout << "Shuffle (1 for yes, 0 for no): ";
                bool shuffle;
                cin >> shuffle;
                prefs.setShuffle(shuffle);
                cout << "Enter theme: ";
                string theme;
                cin.ignore();
                getline(cin, theme);
                prefs.setTheme(theme);
                cout << "Preferences updated." << endl;
                break;
            }
            case 10: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 10);

    return 0;
}
