import './index.css';
import * as React from 'react';
import * as ReactDOM from 'react-dom/client';
import { createBrowserRouter, RouterProvider } from 'react-router-dom';

// Componentes
import App from './App';

import Bootstrap from './components/shared/Bootstrap';
import Navbar from './components/shared/Navbar';
import Footer from './components/shared/Footer';


import AdminUsuarios from './components/admins/AdminUsuarios';
import SolicitudesAutos from './components/recepcionistas/SolicitudesAutos';
import SolicitudesViajes from './components/recepcionistas/SolicitudesViajes';
import Viajes from './components/usuarios/Viajes';
import RentaAutos from './components/usuarios/RentaAutos';

// Rutas
const Router = createBrowserRouter([
  {
    path: "/",
    element: <App />,
  },
  // Rutas para Administradores
  {
    path: "/AdminUsuarios",
    element: <AdminUsuarios />,
  },
  // Rutas para Recepcionistas
  {
    path: "/SolicitudesAutos",
    element: <SolicitudesAutos />,
  },
  {
    path: "/SolicitudesViajes",
    element: <SolicitudesViajes />,
  },
  // Rutas para Usuarios
  {
    path: "/Viajes",
    element: <Viajes />,
  },
  {
    path: "/RentaAutos",
    element: <RentaAutos />,
  }
]);

// Color Fondo Principal
document.body.style = 'background: #2B353A;';


//Render
ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <Bootstrap />
    <Navbar />
    <br /><br />
    <div className="Fondo">
      <RouterProvider router={Router} />
    </div>
    <br /><br /><br />
    <Footer />
  </React.StrictMode>
);
