#pragma once
#pragma once

#include <type_traits>
#include <concepts>

#include <functional>
#include <utility>
#include <chrono>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>

namespace logfmtxx {
	enum class level {
		debug,
		info,
		warn,
		error
	};

	namespace details {
		template <typename T>
		concept as_string_trait = requires(T t) {
			{ t.as_string( ) } -> std::same_as<std::string>;
		};

		template <typename T>
		concept serializable_trait = (
		  std::is_convertible_v<T, std::string>
		  || as_string_trait<T>
		  || std::is_arithmetic_v<T>
		  || std::is_same_v<T, std::chrono::system_clock::time_point>
		  || std::is_same_v<T, level>
		);

		template <serializable_trait T>
		std::string serialize(const T& value) {
			if constexpr (std::is_convertible_v<T, std::string>) {
				auto stream = std::ostringstream{};
				stream << std::quoted(value);
				return stream.str( );
			}
			else if constexpr (as_string_trait<T>) {
				auto stream = std::ostringstream{};
				stream << std::quoted(value.as_string( ));
				return stream.str( );
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				return std::to_string(value);
			}
			else if constexpr (std::is_same_v<T, std::chrono::system_clock::time_point>) {
				auto time = std::chrono::system_clock::to_time_t(value);
				auto stream = std::ostringstream{};
				stream << std::put_time(std::gmtime(&time), "%Y-%m-%dT%H:%M:%SZ");
				return stream.str( );
			}
			else if constexpr (std::is_same_v<T, level>) {
				switch (value) {
				case level::debug: return "debug";
				case level::info:  return "info";
				case level::warn:  return "warn";
				case level::error: return "error";
				}
			}

			return "";
		}

		using field_kv_type = std::pair<std::string, std::string>;

		struct record {
			level lvl;
			std::chrono::system_clock::time_point ts;
			std::string msg;

			field_kv_type* global_ctx;
			std::size_t global_ctx_size;

			field_kv_type* local_ctx;
			std::size_t local_ctx_size;
		};
	}

	template <details::serializable_trait T>
	struct field {
		std::string key;
		T value;
	};

	template <typename T>
	concept printer_trait = requires(T t, const std::string & msg) {
		{ t(msg) };
	};

	template <
		typename clock_type = std::chrono::system_clock,
		printer_trait printer_type = std::function<void(const std::string&)>
	>
	class logger {
	public:
		template <typename... Args>
		logger(
		  printer_type printer,
		  field<Args>... fields
		) : m_printer(printer) {
			m_extras.reserve(sizeof...(Args));
			(m_extras.push_back({ fields.key, details::serialize(fields.value) }), ...);
		}

		template <typename... Args>
		void log(level level, const std::string& message, field<Args>... fields) {
			auto record = details::record{
			  .lvl = level,
			  .ts = clock_type::now( ),
			  .msg = message,
			  .global_ctx = m_extras.data( ),
			  .global_ctx_size = m_extras.size( )
			};

			std::array<details::field_kv_type, sizeof...(Args)> local_ctx = {
			  details::field_kv_type{fields.key, details::serialize(fields.value)}...
			};

			record.local_ctx = local_ctx.data( );
			record.local_ctx_size = local_ctx.size( );

			m_printer(format(record));
		}

		template <typename... Args>
		void debug(const std::string& message, field<Args>... fields) {
			log(level::debug, message, fields...);
		}

		template <typename... Args>
		void info(const std::string& message, field<Args>... fields) {
			log(level::info, message, fields...);
		}

		template <typename... Args>
		void warn(const std::string& message, field<Args>... fields) {
			log(level::warn, message, fields...);
		}

		template <typename... Args>
		void error(const std::string& message, field<Args>... fields) {
			log(level::error, message, fields...);
		}

	private:
		std::string format(const details::record& record) {
			auto stream = std::ostringstream{};

			stream << "time=" << details::serialize(record.ts) << " ";
			stream << "level=" << details::serialize(record.lvl) << " ";
			stream << "message=" << std::quoted(record.msg);

			for (auto i = 0; i < record.global_ctx_size; ++i) {
				const auto& [key, value] = record.global_ctx[ i ];
				stream << " " << key << "=" << value;
			}

			for (auto i = 0; i < record.local_ctx_size; ++i) {
				const auto& [key, value] = record.local_ctx[ i ];
				stream << " " << key << "=" << value;
			}

			return stream.str( );
		}

	private:
		printer_type m_printer;
		std::vector<details::field_kv_type> m_extras;
	};
}