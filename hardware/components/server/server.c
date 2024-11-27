#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8080

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls){

                            const char *json;
                            struct MHD_Response *response;
                            int ret;

                            if(strcmp(method, "GET") != 0)
                                return MHD_NO;

                            if(strcmp(url, "/api/data") == 0){
                                json = "{\"message\": \"Hello World\"}";
                                response = MHD_create_response_from_buffer(strlen(json), (void *)json, MHD_RESPMEM_PERSISTENT);
                                MHD_add_response_header(response, "Content-Type", "application/json");
                                ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                                MHD_destroy_response(response);
                                return ret;
                            }
                            
                            return MHD_NO;
                         }

int server_init(void) {
   struct MHD_Daemon *daemon;

   daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}