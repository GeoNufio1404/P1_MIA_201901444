import './index.css';
import * as React from 'react';
import * as ReactDOM from 'react-dom/client';
import { createBrowserRouter, RouterProvider } from 'react-router-dom';

// Componentes
import App from './App';

import Bootstrap from './shared/Bootstrap';
import Navbar from './shared/Navbar';
import Footer from './shared/Footer';


import TablaUsuarios from './components/admins/TablaUsuarios';

import AST from './components/AST';
import TablaSimbolos from './components/TablaSimbolos';
import TablaTokens from './components/TablaTokens';

// Rutas
const Router = createBrowserRouter([
  {
    path: "/",
    element: <App />,
  },
  {
    path: "/AST",
    element: <AST />,
  },
  {
    path: "/TablaUsuarios",
    element: <TablaUsuarios />,
  },
  {
    path: "/TablaSimbolos",
    element: <TablaSimbolos />,
  },
  {
    path: "/TablaTokens",
    element: <TablaTokens />,
  },
]);

// Color Fondo Principal
document.body.style = 'background: #2B353A;';


//Render
ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <Bootstrap />
    <Navbar />
    <br />
    <div className="Fondo">
      <RouterProvider router={Router} />
    </div>
    <br />
    <Footer />
  </React.StrictMode>
);
