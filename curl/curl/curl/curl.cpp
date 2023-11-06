#include <iostream>
#include <curl/curl.h>

// Callback function to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Set the URL you want to request
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.dictionaryapi.dev/api/v2/entries/en/helloo");

        // Set the callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Request was successful, 'response' now contains the HTTP response
            std::cout << "Response: " << response << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Failed to initialize libcurl." << std::endl;
    }

    return 0;
}