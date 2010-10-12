
.. tema:: he

=============
Herència
=============

.. exercici::
   ::

      class Girafa : public Animal {
        float longitud_coll;
      };


.. exercici::
   ::

     w.x = 'e';      // error (tipus)
     y.s = "qwerty"; // ok
     v.q = 3;        // error (tipus)
     w.p = true;     // error
     v.b = 81;       // ok
     z.d = 5.01;     // ok
     v.x = 55.34;    // ok
     y.x = 0.7;      // error
     x.a = 'A';      // ok
     z.a = '$';      // ok
     x.b = 1;        // ok
     y.b = 3;        // ok

.. exercici::
   ::

      class Camera : public Gadget {
        int _megapixels;
      public:
        Camera(float pes, int Mpx);
      };

      Camera::Camera(float pes, int Mpx)
        : Gadget(pes)
      {
        _megapixels = Mpx;
      }

.. exercici::
   ::

      Z::Z(int a, char b, string s, float f) 
        : Y(s), _x(a, b)
      {
        _f = f;
      }
      
   
