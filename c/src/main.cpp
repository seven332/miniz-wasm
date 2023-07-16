#include <emscripten/bind.h>
#include <miniz.h>
#include <miniz_zip.h>

#include <array>
#include <string>

static emscripten::val zip_reader_init_mem(const std::string& data) {
    auto* zip = new mz_zip_archive;
    mz_zip_zero_struct(zip);
    auto succeed = mz_zip_reader_init_mem(zip, data.data(), data.size(), 0);
    if (succeed) {
        return emscripten::val(zip);
    } else {
        return emscripten::val::undefined();
    }
}

static void zip_reader_end(mz_zip_archive* zip) {
    mz_zip_reader_end(zip);
}

static mz_uint zip_reader_get_num_files(mz_zip_archive* zip) {
    return mz_zip_reader_get_num_files(zip);
}

static bool zip_reader_is_file_a_directory(mz_zip_archive* zip, mz_uint file_index) {
    return mz_zip_reader_is_file_a_directory(zip, file_index);
}

static bool zip_reader_is_file_encrypted(mz_zip_archive* zip, mz_uint file_index) {
    return mz_zip_reader_is_file_encrypted(zip, file_index);
}

static bool zip_reader_is_file_supported(mz_zip_archive* zip, mz_uint file_index) {
    return mz_zip_reader_is_file_a_directory(zip, file_index);
}

static emscripten::val zip_reader_get_filename(mz_zip_archive* zip, mz_uint file_index) {
    std::array<char, 256> buffer;
    auto read = mz_zip_reader_get_filename(zip, file_index, buffer.data(), buffer.size());
    if (read == 0) {
        return emscripten::val::undefined();
    } else {
        return emscripten::val::u8string(buffer.data());
    }
}

EMSCRIPTEN_BINDINGS(miniz) {
    emscripten::function("zip_reader_init_mem", &zip_reader_init_mem);
    emscripten::function("zip_reader_end", &zip_reader_end, emscripten::allow_raw_pointers());
    emscripten::function("zip_reader_get_num_files", &zip_reader_get_num_files, emscripten::allow_raw_pointers());
    emscripten::function(
        "zip_reader_is_file_a_directory",
        &zip_reader_is_file_a_directory,
        emscripten::allow_raw_pointers()
    );
    emscripten::function(
        "zip_reader_is_file_encrypted",
        &zip_reader_is_file_encrypted,
        emscripten::allow_raw_pointers()
    );
    emscripten::function(
        "zip_reader_is_file_supported",
        &zip_reader_is_file_supported,
        emscripten::allow_raw_pointers()
    );
    emscripten::function("zip_reader_get_filename", &zip_reader_get_filename, emscripten::allow_raw_pointers());
    emscripten::class_<mz_zip_archive>("zip_archive");
}
