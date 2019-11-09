#pragma once

#include "Poco/Util/Application.h"
#include "Poco/FileStream.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "../../qrcode/QrCode.hpp"

namespace Reach {

	using Poco::Util::Application;
	using Poco::FileOutputStream;
	using qrcodegen::QrCode;

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
			/// const char *text = "Hello, world!";              // User-supplied text
			const QrCode::Ecc errCorLvl = QrCode::Ecc::QUARTILE;  // Error correction level

			// Make and print the QR Code symbol
			const QrCode qr = QrCode::encodeText(_text.data(), errCorLvl);
			printQr(qr);
			//std::cout << qr.toSvgString(4) << std::endl;
			std::cout << "version : " << qr.getVersion() << std::endl
				<< "mask : " << qr.getMask() << std::endl;

			FileOutputStream ofs(_path);
			ofs << qr.toSvgString(4) << std::endl;
			ofs.close();
		}
		void printQr(const QrCode &qr) {
			int border = 4;

			for (int y = -border; y < qr.getSize() + border; y++) {
				for (int x = -border; x < qr.getSize() + border; x++) {
					std::cout << (qr.getModule(x, y) ? "##" : "  ");
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
