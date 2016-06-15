

class JRecord
{
  public:
   JRecord( int id, int time )
      :m_id(id), m_time(time)
      {}

   int GetTime( )
      {
	 return m_time;
      }
   int GetID( )
      {
	 return m_id;
      }

  private:
   int m_id;
   int m_time;
};
