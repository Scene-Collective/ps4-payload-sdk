// Copyright (C) 2013       Hykem <hykem@hotmail.com>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/gpl-2.0.txt

#include "file.h"
#include "libc.h"
#include "strings.h"

#include "pkg.h"

#define EOF '\00'

// Helper functions.
static inline uint16_t bswap_16(uint16_t val) {
  return ((val & (uint16_t)0x00ffU) << 8) | ((val & (uint16_t)0xff00U) >> 8);
}

static inline uint32_t bswap_32(uint32_t val) {
  return ((val & (uint32_t)0x000000ffUL) << 24) | ((val & (uint32_t)0x0000ff00UL) << 8) | ((val & (uint32_t)0x00ff0000UL) >> 8) | ((val & (uint32_t)0xff000000UL) >> 24);
}

int isfpkg(char *pkgfn) {
  int result = 0;
  char buffer[5];
  FILE *in = NULL;
  struct cnt_pkg_main_header m_header;
  struct cnt_pkg_content_header c_header;
  memset_s(&m_header, sizeof(struct cnt_pkg_main_header), 0, sizeof(struct cnt_pkg_main_header));
  memset_s(&c_header, sizeof(struct cnt_pkg_main_header), 0, sizeof(struct cnt_pkg_content_header));

  if ((in = fopen(pkgfn, "rb")) == NULL) {
    result = 1;
  } else {
    fseek(in, 1, SEEK_SET);
    fread(buffer, 1, 4, in);
    if (strcmp(buffer, "CNT@") == 0) {
      result = 0;
    } else {
      fseek(in, 0, SEEK_SET);
      fread(&m_header, 1, 0x180, in);

      if (m_header.magic != PS4_PKG_MAGIC) {
        result = 2;
      } else if (bswap_32(m_header.type) != 1) {
        result = 3;
      }
    }
  }

  fclose(in);
  return result;
}

static void _mkdir(const char *dir) {
  char tmp[256];
  char *p = NULL;

  snprintf(tmp, sizeof(tmp), "%s", dir);
  for (p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = 0;
      mkdir(tmp, 0777);
      *p = '/';
    }
  }
}

static char *get_entry_name_by_type(uint32_t type) {
  char *entry_name = malloc(32);

  if ((type >= 0x1201) && (type <= 0x121F)) {
    sprintf(entry_name, "icon0_%02u.png", type - 0x1201);
  } else if ((type >= 0x1241) && (type <= 0x125F)) {
    sprintf(entry_name, "pic1_%02u.png", type - 0x1241);
  } else if ((type >= 0x1261) && (type <= 0x127F)) {
    sprintf(entry_name, "changeinfo/changeinfo_%02u.xml", type - 0x1261);
  } else if ((type >= 0x1281) && (type <= 0x129F)) {
    sprintf(entry_name, "icon0_%02u.dds", type - 0x1281);
  } else if ((type >= 0x12C1) && (type <= 0x12DF)) {
    sprintf(entry_name, "pic1_%02u.dds", type - 0x12C1);
  } else if ((type >= 0x1400) && (type <= 0x1463)) {
    sprintf(entry_name, "trophy/trophy%02u.trp", type - 0x1400);
  } else if ((type >= 0x1600) && (type <= 0x1609)) {
    sprintf(entry_name, "keymap_rp/%03u.png", type - 0x1600);
  } else if ((type >= 0x1610) && (type <= 0x17F9)) {
    sprintf(entry_name, "keymap_rp/%02u/%03u.png", (type - 0x1610) / 0x10, (type - 0x1610) % 0x10);
  } else {
    free(entry_name);
    entry_name = NULL;
    switch (type) {
      case 0x0400:
        entry_name = "license.dat";
        break;
      case 0x0401:
        entry_name = "license.info";
        break;
      case 0x0402:
        entry_name = "nptitle.dat";
        break;
      case 0x0403:
        entry_name = "npbind.dat";
        break;
      case 0x0404:
        entry_name = "selfinfo.dat";
        break;
      case 0x0406:
        entry_name = "imageinfo.dat";
        break;
      case 0x0407:
        entry_name = "target-deltainfo.dat";
        break;
      case 0x0408:
        entry_name = "origin-deltainfo.dat";
        break;
      case 0x0409:
        entry_name = "psreserved.dat";
        break;
      case 0x1000:
        entry_name = "param.sfo";
        break;
      case 0x1001:
        entry_name = "playgo-chunk.dat";
        break;
      case 0x1002:
        entry_name = "playgo-chunk.sha";
        break;
      case 0x1003:
        entry_name = "playgo-manifest.xml";
        break;
      case 0x1004:
        entry_name = "pronunciation.xml";
        break;
      case 0x1005:
        entry_name = "pronunciation.sig";
        break;
      case 0x1006:
        entry_name = "pic1.png";
        break;
      case 0x1007:
        entry_name = "pubtoolinfo.dat";
        break;
      case 0x1008:
        entry_name = "app/playgo-chunk.dat";
        break;
      case 0x1009:
        entry_name = "app/playgo-chunk.sha";
        break;
      case 0x100A:
        entry_name = "app/playgo-manifest.xml";
        break;
      case 0x100B:
        entry_name = "shareparam.json";
        break;
      case 0x100C:
        entry_name = "shareoverlayimage.png";
        break;
      case 0x100D:
        entry_name = "save_data.png";
        break;
      case 0x100E:
        entry_name = "shareprivacyguardimage.png";
        break;
      case 0x1200:
        entry_name = "icon0.png";
        break;
      case 0x1220:
        entry_name = "pic0.png";
        break;
      case 0x1240:
        entry_name = "snd0.at9";
        break;
      case 0x1260:
        entry_name = "changeinfo/changeinfo.xml";
        break;
      case 0x1280:
        entry_name = "icon0.dds";
        break;
      case 0x12A0:
        entry_name = "pic0.dds";
        break;
      case 0x12C0:
        entry_name = "pic1.dds";
        break;
    }
  }

  return entry_name;
}

int unpkg(char *pkgfn, char *tidpath) {
  struct cnt_pkg_main_header m_header;
  struct cnt_pkg_content_header c_header;
  memset(&m_header, 0, sizeof(struct cnt_pkg_main_header));
  memset(&c_header, 0, sizeof(struct cnt_pkg_content_header));

  int fdin = open(pkgfn, O_RDONLY, 0);
  if (fdin == -1) {
    return 1;
  }

  // Read in the main CNT header (size seems to be 0x180 with 4 hashes included).
  lseek(fdin, 0, SEEK_SET);
  read(fdin, &m_header, 0x180);

  if (m_header.magic != PS4_PKG_MAGIC) {
    return 2;
  }

  // Seek to offset 0x400 and read content associated header (size seems to be 0x80 with 2 hashes included).
  lseek(fdin, 0x400, SEEK_SET);
  read(fdin, &c_header, 0x80);

  // Locate the entry table and list each type of section inside the PKG/CNT file.
  lseek(fdin, bswap_32(m_header.file_table_offset), SEEK_SET);

  struct cnt_pkg_table_entry *entries = malloc(sizeof(struct cnt_pkg_table_entry) * bswap_16(m_header.table_entries_num));
  if (entries == NULL) {
    close(fdin);
    return 3;
  }
  memset(entries, 0, sizeof(struct cnt_pkg_table_entry) * bswap_16(m_header.table_entries_num));
  int i;
  for (i = 0; i < bswap_16(m_header.table_entries_num); i++) {
    read(fdin, &entries[i], 0x20);
  }

  // Vars for file name listing.
  struct file_entry *entry_files = malloc(sizeof(struct file_entry) * bswap_16(m_header.table_entries_num));
  if (entry_files == NULL) {
    close(fdin);
    free(entries);
    return 4;
  }
  memset(entry_files, 0, sizeof(struct file_entry) * bswap_16(m_header.table_entries_num));
  char *file_name_list[256];
  int file_name_index = 0;
  int file_count = 0;

  // Var for file writing.
  unsigned char *entry_file_data;

  // Search through the data entries and locate the name table entry.
  // This section should keep relevant strings for internal files inside the PKG/CNT file.
  for (i = 0; i < bswap_16(m_header.table_entries_num); i++) {
    if (bswap_32(entries[i].type) == PS4_PKG_ENTRY_TYPE_NAME_TABLE) {
      lseek(fdin, bswap_32(entries[i].offset) + 1, SEEK_SET);
      while ((file_name_list[file_name_index] = read_string(fdin))[0] != '\0') {
        file_name_index++;
      }
    }
  }

  // Search through the data entries and locate file entries.
  // These entries need to be mapped with the names collected from the name table.
  for (i = 0; i < bswap_16(m_header.table_entries_num); i++) {
    // Use a predefined list for most file names.
    entry_files[i].name = get_entry_name_by_type(bswap_32(entries[i].type));
    entry_files[i].offset = bswap_32(entries[i].offset);
    entry_files[i].size = bswap_32(entries[i].size);

    if (((bswap_32(entries[i].type) & PS4_PKG_ENTRY_TYPE_FILE1) == PS4_PKG_ENTRY_TYPE_FILE1) || (((bswap_32(entries[i].type) & PS4_PKG_ENTRY_TYPE_FILE2) == PS4_PKG_ENTRY_TYPE_FILE2))) {
      // If a file was found and it's name is not on the predefined list, try to map it with
      // a name from the name table.
      if (entry_files[i].name == NULL) {
        entry_files[i].name = file_name_list[file_count];
      }
      if (entry_files[i].name != NULL) {
        file_count++;
      }
    }
  }

  // Set up the output directory for file writing.
  char dest_path[256];
  char title_id[256];

  memset(title_id, 0, 256);
  memcpy(title_id, tidpath, 255);
  mkdir(title_id, 0777);

  // Search through the entries for mapped file data and output it.
  for (i = 0; i < bswap_16(m_header.table_entries_num); i++) {
    entry_file_data = (unsigned char *)realloc(NULL, entry_files[i].size);

    lseek(fdin, entry_files[i].offset, SEEK_SET);
    read(fdin, entry_file_data, entry_files[i].size);

    if (entry_files[i].name == NULL) continue;

    sprintf(dest_path, "%s/sce_sys/%s", title_id, entry_files[i].name);

    _mkdir(dest_path);

    int fdout = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdout != -1) {
      write(fdout, entry_file_data, entry_files[i].size);
      close(fdout);
    } else {
      close(fdin);
      free(entries);
      free(entry_files);
      return 5;
    }
  }

  // Clean up.
  close(fdin);

  free(entries);
  free(entry_files);

  return 0;
}
