#include "Reach/Data/SessionHolder.h"

namespace Reach {
namespace Data {

SessionHolder::SessionHolder(SessionImpl* pSessionImpl)
	:_pImpl(pSessionImpl, true), _shutdown(false)
{

}

SessionHolder::~SessionHolder()
{

}

void SessionHolder::shutdown()
{
	if (_shutdown) return;
	_shutdown = true;

	_pImpl->close();
}

} } ///  namespace Reach::Data