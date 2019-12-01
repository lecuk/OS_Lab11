
fprintf(file, "%s", book->text);
fclose(file);
fileMapView[FILEMAP_FLAG_ADDRESS] = 1;
strcpy(&fileMapView[FILEMAP_PATH_ADDRESS], path);
printf("Successfully posted book \"%s\"\n", book->name);
