#pragma once

namespace agl
{
	class Event
	{
		private:
			int type;
			int close;
		public:
			const static int WindowClose;

			void setType(int type);

	};
} // namespace agl
