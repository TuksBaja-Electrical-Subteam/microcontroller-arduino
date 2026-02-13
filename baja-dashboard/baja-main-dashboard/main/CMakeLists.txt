idf_component_register(SRCS "main.c" "web_server.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES "index.html"
                    PRIV_REQUIRES esp_http_server esp_wifi nvs_flash esp_driver_pcnt esp_driver_gpio)