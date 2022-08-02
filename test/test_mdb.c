#include <stdio.h>

#include "serd/serd.h"

int COUNT = 0;

SerdStatus on_statement(void* handle, SerdStatementFlags flags,
                        const SerdNode* graph,
                        const SerdNode* subject,
                        const SerdNode* predicate,
                        const SerdNode* object,
                        const SerdNode* object_datatype,
                        const SerdNode* object_lang) {
  COUNT++;
  return SERD_SUCCESS;
}

int main(int argc, char* argv[]) {
  char* path = argv[1];
  // Open and point to start of file
  FILE* file = fopen(path, "r");
  fseek(file, 0, SEEK_SET);
  // Initialize reader
  SerdReader* const reader = serd_reader_new(SERD_TURTLE, NULL, NULL, NULL, NULL, on_statement, NULL);
  // Start reading file
  serd_reader_start_stream(reader, file, NULL, true);
  // Read until EOF
  while (serd_reader_read_chunk(reader) != SERD_FAILURE) {
    continue;
  }
  // Finish reading
  serd_reader_end_stream(reader);  
  // Cleanup
  serd_reader_free(reader);
  fclose(file);

  printf("COUNT: %d\n", COUNT);

  return 0;
}