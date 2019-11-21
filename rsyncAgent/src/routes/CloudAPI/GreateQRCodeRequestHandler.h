#pragma once

#include "Poco/Util/Application.h"
#include "Poco/FileStream.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "../../qrcode/QrCode.hpp"
#include "Poco/StreamConverter.h"
#include "Poco/TextConverter.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/UTF16Encoding.h"

namespace Reach {

	using Poco::Util::Application;
	using Poco::FileOutputStream;
	using qrcodegen::QrCode;
	using Poco::OutputStreamConverter;
	using Poco::UTF8Encoding;
	using Poco::UTF16Encoding;
	using Poco::TextConverter;
	using Poco::UnicodeConverter;
	///RS_GreateQRCode
	class GreateQRCode : public Command
	{
	public:
		GreateQRCode(const std::string& text, const std::string& path)
			:_text(text), _path(path)
		{
		}

		void run()
		{
			Application& app = Application::instance();
			/// const char *text = "Hello, world!";              // User-supplied text
			const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

			// Make and print the QR Code symbol
			const QrCode qr = QrCode::encodeText(_text.data(), errCorLvl);
			printQr(qr);
			poco_information_f2(app.logger(), "version : %d, mask : %d", qr.getVersion(), qr.getMask());

			FileOutputStream ofs(_path);
			ofs << qr.toSvgString(4) << std::endl;
			ofs.close();
		}

		void printQr(const QrCode &qr) {

			int border = 4;
			HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD written;

			for (int y = -border; y < qr.getSize() + border; y++) {
				for (int x = -border; x < qr.getSize() + border; x++) {
					std::string utf8 = (qr.getModule(x, y) ? "\xE2\x96\xA0" : "  ");
					Poco::UTF16String ucs2;
					UnicodeConverter::convert(utf8, ucs2);
					
					WriteConsoleW(_hConsole, ucs2.data(), static_cast<DWORD>(ucs2.size()), &written, NULL);
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	private:
		std::string _text;
		std::string _path;
	};

	class GreateQRCodeRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string qrcode = form.get("qrcode", "");
			std::string path = form.get("path", "");
			GreateQRCode command(qrcode, path);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}
