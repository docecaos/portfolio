#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

// Configurações do Wi-Fi
const char* ssid = "codegabriel";
const char* password = "";  // Deixe vazio para rede aberta

// DNS e servidor
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// Página HTML estilizada
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Code Gabriel - Sites Incríveis</title>
  <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;500;600;700&display=swap" rel="stylesheet">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
  <style>
    :root {
      --primary: #00bfff;
      --primary-dark: #0099cc;
      --secondary: #00ffcc;
      --dark-bg: #0f0f0f;
      --darker-bg: #0a0a0a;
      --card-bg: #1c1c1c;
      --text-light: #f0f0f0;
      --text-muted: #aaaaaa;
      --transition: all 0.3s cubic-bezier(0.25, 0.8, 0.25, 1);
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Outfit', sans-serif;
      background: linear-gradient(135deg, var(--dark-bg), #1a1a1a);
      color: var(--text-light);
      scroll-behavior: smooth;
      overflow-x: hidden;
      line-height: 1.6;
    }

    /* Header */
    header {
      padding: 3rem 1rem 1rem;
      text-align: center;
      position: relative;
      overflow: hidden;
      min-height: 60vh;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
    }

    header::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: radial-gradient(circle at center, rgba(0, 191, 255, 0.1) 0%, transparent 70%);
      z-index: -1;
    }

    header h1 {
      font-size: 2.8rem;
      font-weight: 700;
      background: linear-gradient(to right, var(--secondary), var(--primary));
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      margin-bottom: 0.5rem;
      letter-spacing: -0.5px;
      text-shadow: 0 2px 10px rgba(0, 191, 255, 0.3);
    }

    header p.tagline {
      color: var(--text-muted);
      font-size: 1.1rem;
      max-width: 600px;
      margin: 0 auto 2rem;
      position: relative;
    }

    .header-cta {
      margin-top: 2rem;
    }

    /* Marketing Section */
    .marketing-top {
      text-align: center;
      padding: 3rem 1.5rem;
      background: rgba(22, 22, 22, 0.8);
      backdrop-filter: blur(5px);
      border-radius: 20px;
      max-width: 800px;
      margin: 2rem auto;
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
      border: 1px solid rgba(255, 255, 255, 0.05);
      transform: translateY(0);
      transition: var(--transition);
    }

    .marketing-top:hover {
      transform: translateY(-5px);
      box-shadow: 0 12px 40px rgba(0, 191, 255, 0.2);
    }

    .marketing-top h2 {
      font-size: 1.8rem;
      margin-bottom: 1rem;
      color: var(--primary);
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 10px;
    }

    .marketing-top p {
      font-size: 1.1rem;
      color: var(--text-muted);
      max-width: 600px;
      margin: 0 auto;
    }

    /* CTA Section */
    .cta-section {
      text-align: center;
      padding: 4rem 1.5rem;
      position: relative;
    }

    .cta-section::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: linear-gradient(135deg, rgba(0, 191, 255, 0.05) 0%, transparent 100%);
      z-index: -1;
    }

    .cta-section h2 {
      font-size: 2.2rem;
      margin-bottom: 1.5rem;
      background: linear-gradient(to right, var(--text-light), var(--primary));
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .cta-section p {
      font-size: 1.1rem;
      color: var(--text-muted);
      margin-bottom: 2rem;
      max-width: 600px;
      margin-left: auto;
      margin-right: auto;
    }

    .cta-button {
      padding: 1rem 2.5rem;
      background: linear-gradient(to right, var(--primary), var(--secondary));
      border: none;
      border-radius: 50px;
      font-size: 1.1rem;
      font-weight: 600;
      color: #000;
      cursor: pointer;
      transition: var(--transition);
      display: inline-flex;
      align-items: center;
      gap: 10px;
      box-shadow: 0 4px 15px rgba(0, 191, 255, 0.3);
      position: relative;
      overflow: hidden;
    }

    .cta-button::before {
      content: '';
      position: absolute;
      top: 0;
      left: -100%;
      width: 100%;
      height: 100%;
      background: linear-gradient(90deg, transparent, rgba(255, 255, 255, 0.2), transparent);
      transition: 0.5s;
    }

    .cta-button:hover {
      transform: translateY(-3px);
      box-shadow: 0 8px 25px rgba(0, 191, 255, 0.4);
    }

    .cta-button:hover::before {
      left: 100%;
    }

    .cta-button:active {
      transform: translateY(1px);
    }

    /* Services Section */
    .services {
      padding: 5rem 1rem;
      text-align: center;
      position: relative;
    }

    .services::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: rgba(17, 17, 17, 0.9);
      z-index: -1;
    }

    .services h3 {
      font-size: 1.8rem;
      margin-bottom: 3rem;
      position: relative;
      display: inline-block;
    }

    .services h3::after {
      content: '';
      position: absolute;
      bottom: -10px;
      left: 50%;
      transform: translateX(-50%);
      width: 60px;
      height: 3px;
      background: linear-gradient(to right, var(--primary), var(--secondary));
      border-radius: 3px;
    }

    .service-cards {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      gap: 2rem;
      max-width: 1200px;
      margin: 0 auto;
    }

    .card {
      background: var(--card-bg);
      border-radius: 20px;
      padding: 2rem 1.5rem;
      width: 100%;
      max-width: 350px;
      transition: var(--transition);
      border: 1px solid rgba(255, 255, 255, 0.05);
      position: relative;
      overflow: hidden;
    }

    .card::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 5px;
      background: linear-gradient(to right, var(--primary), var(--secondary));
    }

    .card:hover {
      transform: translateY(-10px);
      box-shadow: 0 15px 30px rgba(0, 0, 0, 0.3);
    }

    .card .icon {
      font-size: 2.5rem;
      margin-bottom: 1.5rem;
      color: var(--primary);
      transition: var(--transition);
    }

    .card:hover .icon {
      transform: scale(1.1);
      color: var(--secondary);
    }

    .card h4 {
      font-size: 1.4rem;
      margin-bottom: 1rem;
      color: var(--text-light);
    }

    .card p {
      font-size: 1rem;
      color: var(--text-muted);
    }

    /* Footer */
    footer {
      padding: 3rem 1rem;
      text-align: center;
      background: var(--darker-bg);
      font-size: 0.9rem;
      color: var(--text-muted);
      position: relative;
    }

    footer::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 1px;
      background: linear-gradient(to right, transparent, rgba(255, 255, 255, 0.1), transparent);
    }

    .social-links {
      display: flex;
      justify-content: center;
      gap: 1.5rem;
      margin-bottom: 1.5rem;
    }

    .social-links a {
      color: var(--text-muted);
      font-size: 1.2rem;
      transition: var(--transition);
      width: 40px;
      height: 40px;
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      background: rgba(255, 255, 255, 0.05);
    }

    .social-links a:hover {
      color: var(--primary);
      transform: translateY(-3px);
      background: rgba(0, 191, 255, 0.1);
    }

    /* Animations */
    @keyframes float {
      0%, 100% { transform: translateY(0); }
      50% { transform: translateY(-10px); }
    }

    .floating {
      animation: float 3s ease-in-out infinite;
    }

    /* Particles */
    .particles {
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      overflow: hidden;
      z-index: -1;
    }

    .particle {
      position: absolute;
      background: rgba(0, 191, 255, 0.5);
      border-radius: 50%;
      pointer-events: none;
    }

    /* Responsive */
    @media (min-width: 768px) {
      header {
        padding: 4rem 1rem 2rem;
      }

      header h1 {
        font-size: 3.5rem;
      }

      .marketing-top {
        padding: 3.5rem 2rem;
      }

      .marketing-top h2 {
        font-size: 2.2rem;
      }

      .cta-section h2 {
        font-size: 2.8rem;
      }

      .services h3 {
        font-size: 2.2rem;
      }
    }

    @media (min-width: 992px) {
      header h1 {
        font-size: 4rem;
      }
    }
  </style>
</head>
<body>
  <div class="particles" id="particles"></div>
  
  <header>
    <h1>Code Gabriel</h1>
    <p class="tagline">Criando experiências digitais memoráveis</p>
    <div class="header-cta">
      <button class="cta-button" id="whatsappBtn">
        <i class="fab fa-whatsapp"></i> Fale comigo agora
      </button>
    </div>
  </header>

  <section class="marketing-top">
    <h2><i class="fas fa-bolt"></i> Gostou da estratégia de marketing?</h2>
    <p>Esse site apareceu porque você se conectou ao nosso Wi-Fi. Imagine o que podemos fazer para seu negócio se destacar com um site personalizado e estratégias digitais eficientes.</p>
  </section>

  <section class="cta-section">
    <h2>Transforme sua presença online</h2>
    <p>Desenvolvo sites modernos, responsivos e otimizados que convertem visitantes em clientes.</p>
    <button class="cta-button" id="whatsappBtn2">
      <i class="fab fa-whatsapp"></i> Fale comigo no WhatsApp
    </button>
  </section>

  <section class="services">
    <h3>O que eu ofereço</h3>
    <div class="service-cards">
      <div class="card floating" style="animation-delay: 0.2s;">
        <div class="icon">
          <i class="fas fa-user-tie"></i>
        </div>
        <h4>Sites Pessoais</h4>
        <p>Portfólios, blogs e páginas de apresentação com design único e totalmente responsivo para todos os dispositivos.</p>
      </div>
      <div class="card floating" style="animation-delay: 0.4s;">
        <div class="icon">
          <i class="fas fa-briefcase"></i>
        </div>
        <h4>Sites Comerciais</h4>
        <p>Landing pages, vitrines digitais e sites institucionais profissionais que aumentam sua credibilidade e vendas.</p>
      </div>
      <div class="card floating" style="animation-delay: 0.6s;">
        <div class="icon">
          <i class="fas fa-magic"></i>
        </div>
        <h4>Interativos & Criativos</h4>
        <p>Experiências web impressionantes com animações, microinterações e designs que contam sua história de forma única.</p>
      </div>
    </div>
  </section>

  <footer>
    <div class="social-links">
      <a href="https://instagram.com/codegabriel" target="_blank"><i class="fab fa-instagram"></i></a>
      <a href="https://wa.me/98985641889" target="_blank"><i class="fab fa-whatsapp"></i></a>
      <a href="mailto:codegabriel.ti@gmail.com"><i class="fas fa-envelope"></i></a>
    </div>
    <p>© 2025 - Desenvolvido por Code Gabriel | Todos os direitos reservados.</p>
    <p style="margin-top: 0.5rem; font-size: 0.8rem;">Feito com <i class="fas fa-heart" style="color: #ff4757;"></i> em São Luís MA</p>
  </footer>

  <script>
    // Botão do WhatsApp
    document.getElementById("whatsappBtn").addEventListener("click", function() {
      window.open("https://wa.me/98985641889", "_blank");
    });
    
    document.getElementById("whatsappBtn2").addEventListener("click", function() {
      window.open("https://wa.me/98985641889", "_blank");
    });

    // Efeito de digitação no header
    const tagline = document.querySelector('.tagline');
    if (tagline) {
      const text = tagline.textContent;
      tagline.textContent = '';
      
      let i = 0;
      const typingEffect = setInterval(() => {
        if (i < text.length) {
          tagline.textContent += text.charAt(i);
          i++;
        } else {
          clearInterval(typingEffect);
        }
      }, 50);
    }

    // Animação ao rolar
    const animateOnScroll = () => {
      const cards = document.querySelectorAll('.card');
      cards.forEach(card => {
        const cardPosition = card.getBoundingClientRect().top;
        const screenPosition = window.innerHeight / 1.3;
        
        if (cardPosition < screenPosition) {
          card.style.opacity = '1';
          card.style.transform = 'translateY(0)';
        }
      });
    };

    // Inicializa as cartas com opacidade 0 para animação
    window.addEventListener('DOMContentLoaded', () => {
      const cards = document.querySelectorAll('.card');
      cards.forEach(card => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(20px)';
        card.style.transition = 'opacity 0.5s ease, transform 0.5s ease';
      });
      
      // Cria partículas
      createParticles();
    });

    window.addEventListener('scroll', animateOnScroll);
    // Dispara uma vez no carregamento
    animateOnScroll();

    // Efeito de partículas
    function createParticles() {
      const particlesContainer = document.getElementById('particles');
      const particleCount = 30;
      
      for (let i = 0; i < particleCount; i++) {
        const particle = document.createElement('div');
        particle.classList.add('particle');
        
        // Tamanho aleatório entre 2px e 5px
        const size = Math.random() * 3 + 2;
        particle.style.width = `${size}px`;
        particle.style.height = `${size}px`;
        
        // Posição aleatória
        particle.style.left = `${Math.random() * 100}%`;
        particle.style.top = `${Math.random() * 100}%`;
        
        // Opacidade aleatória
        particle.style.opacity = Math.random() * 0.5 + 0.1;
        
        // Animação
        const duration = Math.random() * 20 + 10;
        particle.style.animation = `float ${duration}s infinite ease-in-out`;
        particle.style.animationDelay = `${Math.random() * 5}s`;
        
        particlesContainer.appendChild(particle);
      }
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // Inicia ponto de acesso
  WiFi.softAP(ssid, password);
  delay(100);
  Serial.println("Ponto de acesso iniciado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.softAPIP());

  // Redireciona qualquer domínio para o ESP32
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // Rota principal
  server.on("/", []() {
    server.send_P(200, "text/html", index_html);
  });

  // Respostas para o captive portal detection
  server.on("/generate_204", []() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  server.on("/fwlink", []() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  server.on("/hotspot-detect.html", []() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  // Resposta para solicitação de conectividade do Android
  server.on("/connecttest.txt", []() {
    server.send(200, "text/plain", "Microsoft Connect Test");
  });

  // Resposta para solicitação de conectividade do Windows
  server.on("/ncsi.txt", []() {
    server.send(200, "text/plain", "Microsoft NCSI");
  });

  // Resposta para solicitação de conectividade do iOS
  server.on("/library/test/success.html", []() {
    server.send(200, "text/html", "<!DOCTYPE html><html><head><title>Success</title></head><body>Success</body></html>");
  });

  // Captive portal detection do iOS
  server.on("/hotspot.html", []() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  // Captive portal detection do Android
  server.on("/check_network_status.txt", []() {
    server.send(200, "text/plain", "1");
  });

  // Para qualquer outra requisição não tratada
  server.onNotFound([]() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("Servidor iniciado.");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}