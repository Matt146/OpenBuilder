#include "utils.h"

int WIDTH = 1808*2;
int HEIGHT = 1080*2;

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
	return texture;
}

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

std::string ReadFile(std::string fname) {
    FILE* fp = fopen(fname.c_str(), "r");
    std::string buff = "";
    char c;
    while (!feof(fp)) {
        buff += fgetc(fp);
    }
    return buff;
}

float Distance(double x1, double y1, double x2, double y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
} 

double GetCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch);
    double duration = value.count();
    double duration_s = duration / 1000000000.0;
    return duration_s;
}

double Approach(double current, double goal, double dt) {
    double difference = goal - current;

    if (difference > dt) {
        return current + dt;
    } if (difference < -dt) {
        return current-dt;
    }
    return goal;
}

bool CompareDoubles (double A, double B) 
{
   double diff = A - B;
   return (diff < EPSILON) && (-diff < EPSILON);
}

int clamp(int n, int lower, int upper) {
  return std::max(lower, std::min(n, upper));
}

std::vector<SDL_Texture*> LoadAnimationFrames(SDL_Renderer* renderer, std::string animation_name) {
    // read the entire directory
    DIR* animation_dir = opendir(ANIMATION_DIRECTORY);
    if (animation_dir == NULL) {
        std::cout << "\n[Error] Unable to load animation: " << animation_name << " from " << ANIMATION_DIRECTORY;
    }
    struct dirent *d;
    std::vector<std::string> files;
    while ((d = readdir(animation_dir)) != NULL) {
        if (d->d_type == DT_REG) {
            files.push_back(d->d_name);
        }
    }

    for (size_t i = 0; i < files.size(); i++) {
        std::cout << files[i] << std::endl;
    }

    // go through every file in the directory and pick out the ones matching the animation name
    std::string animation_name_temp = animation_name + "_0" + ".bmp";
    std::vector<SDL_Texture*> animation_frames;
    for (size_t i = 1; i < files.size()+1; i++) {
        SDL_Texture* loaded_texture = LoadTexture(renderer, std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp);
        if (loaded_texture != NULL) {
            std::cout << "[^] Loaded animation frame: " << std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp << std::endl;
            animation_frames.push_back(loaded_texture);
        } else {
            std::cout << "[Error] Unable to load animation frame: " << std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp << std::endl;
        }

        // remove file extension
        size_t lastindex = animation_name_temp.find_last_of("."); 
        std::string animation_name_temp_rawname = animation_name_temp.substr(0, lastindex); 

        // change the frame number: ie: animation_0 --> animation_1
        std::vector<std::string> split = split_string(animation_name_temp_rawname, "_");
        animation_name_temp = split[0] + "_" + std::to_string(i) + ".bmp";
    }

    return animation_frames;
}

Animation LoadAnimations(SDL_Renderer* renderer, std::string animation_name) {
    // read the entire directory
    DIR* animation_dir = opendir(ANIMATION_DIRECTORY);
    if (animation_dir == NULL) {
        std::cout << "\n[Error] Unable to load animation: " << animation_name << " from " << ANIMATION_DIRECTORY;
    }
    struct dirent *d;
    std::vector<std::string> files;
    while ((d = readdir(animation_dir)) != NULL) {
        if (d->d_type == DT_REG) {
            files.push_back(d->d_name);
        }
    }

    for (size_t i = 0; i < files.size(); i++) {
        std::cout << files[i] << std::endl;
    }

    // go through every file in the directory and pick out the ones matching the animation name
    std::string animation_name_temp = animation_name + "_0" + ".bmp";
    std::vector<SDL_Texture*> animation_frames;
    for (size_t i = 1; i < files.size()+1; i++) {
        SDL_Texture* loaded_texture = LoadTexture(renderer, std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp);
        if (loaded_texture != NULL) {
            std::cout << "[^] Loaded animation frame: " << std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp << std::endl;
            animation_frames.push_back(loaded_texture);
        } else {
            std::cout << "[Error] Unable to load animation frame: " << std::string(ANIMATION_DIRECTORY) + "/" + animation_name_temp << std::endl;
        }

        // remove file extension
        size_t lastindex = animation_name_temp.find_last_of("."); 
        std::string animation_name_temp_rawname = animation_name_temp.substr(0, lastindex); 

        // change the frame number: ie: animation_0 --> animation_1
        std::vector<std::string> split = split_string(animation_name_temp_rawname, "_");
        animation_name_temp = split[0] + "_" + std::to_string(i) + ".bmp";
    }

    Animation a(renderer, animation_frames);
    return a;
}

template <typename T>
size_t RemoveDuplicatesKeepOrder(std::vector<T>& vec)
{
    std::set<T> seen;

    auto newEnd = std::remove_if(vec.begin(), vec.end(), [&seen](const T& value)
    {
        if (seen.find(value) != std::end(seen))
            return true;

        seen.insert(value);
        return false;
    });

    vec.erase(newEnd, vec.end());

    return vec.size();
}

std::vector<std::string> LoadWorldNames() {
    DIR* worlds_dir = opendir(WORLD_FOLDER_PATH);
    if (worlds_dir == NULL) {
    }
    struct dirent *d;
    std::vector<std::string> files;
    while ((d = readdir(worlds_dir)) != NULL) {
        if (d->d_type == DT_REG) {
            files.push_back(d->d_name);
        }
    }

    // get all the files and split them
    std::vector<std::string> split_files;
    std::vector<std::string>::iterator it;
    for (it = files.begin(); it != files.end(); ++it) {
        std::vector<std::string> file_split = split_string(*it, "_");
        if (file_split.size() > 0) {
            split_files.push_back(file_split[0]);
        }
    }

    RemoveDuplicatesKeepOrder<std::string>(split_files);
    for (size_t j = 0; j < split_files.size(); j++) {
        std::cout << split_files[j] << std::endl;
    }

    return split_files;
}

float SampleLayeredNoise(float value, int seed){
    float noise = 0;
    float frequency = 1;
    float factor = 1;

    FastNoise myNoise; // Create a FastNoise object
    myNoise.SetNoiseType(FastNoise::Simplex); // Set the desired noise type
    myNoise.SetSeed(seed);
    myNoise.SetFrequency(PERLIN_FREQUENCY);
    myNoise.SetInterp(FastNoise::Linear);
    for (int i=0; i<PERLIN_OCTAVES; i++){
        noise = noise + abs(myNoise.GetNoise(value * frequency + i * 0.72354, ONED_PERLIN_STRIP_INDEX) * factor);
        factor *= PERLIN_PERSISTENCE;
        frequency *= PERLIN_ROUGHNESS;
    }

    return noise;
}

bool LeftMouseDown(SDL_Event ev) {
    static bool mouse_down = false;
    if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
        mouse_down = true;
    } if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT) {
        mouse_down = false;
    }

    return mouse_down;
}

bool RightMouseDown(SDL_Event ev) {
    static bool mouse_down = false;
    if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT) {
        mouse_down = true;
    } if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_RIGHT) {
        mouse_down = false;
    }

    return mouse_down;
}
void ReduceFraction(int &numerator, int &denominator) {
        for (int i = denominator * numerator; i > 1; i--) {  
                if ((denominator % i == 0) && (numerator % i == 0)) {  
            denominator /= i;  
                numerator /= i;  
        }  
                  
         }
}